

#include "../WTBamboo.h"

void cP2PClient::StartConnection(uint16 liChannels,void (*lpHandlePackets)(NETWORK_SIGNAL_TYPE lsSignal,uint8 *lpData,uint16 liSize),void (*lpHandleConnection)())
{
    mpSync=0;

    mpPeers=new ENetPeer*[miChannels];
    miPeers=0;
	mpHost = enet_host_create (NULL,miChannels,2,0,0);

	if (mpHost == NULL)
    {
        TRACE("An error occurred while trying to create an ENet client host");
    }



    // Initiate the connection, allocating the two channels 0 and 1.
    mpPeers[0] = enet_host_connect(mpHost, &mcAddress, 2,0);

    if (mpPeers[0] == NULL)
    {
       TRACE("No available peers for initiating an ENet connection.");
    }

    ENetEvent event;

    // Wait up to 5 seconds for the connection attempt to succeed.
    if (enet_host_service (mpHost, & event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
    {
        TRACE("Connection to " << mcAddress.host << ":" << mcAddress.port <<" succeeded");
    }
    else
    {
        enet_peer_reset (mpPeers[0]);
        TRACE("Connection to "<< mcAddress.host << ":" << mcAddress.port << " failed.");
    }

    ++miPeers;
};

cP2PClient::cP2PClient(ENetAddress &lcAddress,uint16 liChannels,void (*lpHandlePackets)(NETWORK_SIGNAL_TYPE lsSignal,uint8 *lpData,uint16 liSize),void (*lpHandleConnection)())
{
    mcAddress=lcAddress;
    StartConnection(liChannels,lpHandlePackets,lpHandleConnection);

}
cP2PClient::cP2PClient(string lsAddress,uint16 liPort,uint16 liChannels,void (*lpHandlePackets)(NETWORK_SIGNAL_TYPE lsSignal,uint8 *lpData,uint16 liSize),void (*lpHandleConnection)()) : cNetworkBase(liChannels,lpHandlePackets,lpHandleConnection)
{
       // Connect to some.server.net:1234.
    enet_address_set_host(&mcAddress, lsAddress.c_str());
    mcAddress.port = liPort;

    StartConnection(liChannels,lpHandlePackets,lpHandleConnection);
}


cP2PClient::~cP2PClient()
{
    if(mpSync) delete mpSync;
}

void cP2PClient::HandleConnection()
{
    TRACE("Client HandleConnection");
//if(mpHandleConnections) mpHandleConnections();
}

void cP2PClient::HandlePacket(NETWORK_SIGNAL_TYPE lsSignal, uint8 *lpData,uint16 liSize)
{
    switch(lsSignal)
    {
        case WT_PACKET_CODE_ADD_CLIENT:
        {
              ENetAddress TempAddress;
                memcpy(&TempAddress.host,lpData,sizeof(uint32));
                memcpy(&TempAddress.port,&(lpData[sizeof(uint32)]),sizeof(uint16));

                mpPeers[miPeers]=enet_host_connect(mpHost, &TempAddress, 2,0);
                ++miPeers;
                if(mpHandleConnections) mpHandleConnections();
                TRACE("Add Peer To Client "<<TempAddress.host<<":"<<TempAddress.port);
        }break;

        case WT_PACKET_CODE_SYNC_START:
        {
            if(mpSync) mpSync->Start();
            else TRACE("Asked to Sync before Sync requested");
        }break;

        case WT_PACKET_CODE_SET_PEER_ID:
        {
            memcpy(&miThisPeerID,lpData,sizeof(uint16));
            TRACE("This PeerID : "<<miThisPeerID);
        } break;

        default:
        {
            if(mpHandlePackets) mpHandlePackets(lsSignal,lpData,liSize);
        }
    };

}

void cP2PClient::SynchStartToSever(void (*lpStartFunction)(void))
{
    mpSync=new cNetworkSyncClient(mpPeers[0],lpStartFunction);
};

cNetworkSyncClient::cNetworkSyncClient(ENetPeer *lpPeer,void (*lpStartFunction)(void))
{
    mpStartFunction=lpStartFunction;
    ENetPacket* packet = enet_packet_create ((uint8*)&cPacketCodes::RequestSync,sizeof(NETWORK_SIGNAL_TYPE),ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send (lpPeer, 0, packet);
};

cNetworkSyncClient::~cNetworkSyncClient()
{

};

void cNetworkSyncClient::StartFunction(void (*lpStartFunction)(void))
{
    mpStartFunction=lpStartFunction;
};
void cNetworkSyncClient::Start()
{
    mpStartFunction();
};
