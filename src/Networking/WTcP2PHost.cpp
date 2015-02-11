
#include "../WTBamboo.h"


cP2PHost::cP2PHost(uint16 liPort, uint16 liChannels,void (*lpHandlePackets)(NETWORK_SIGNAL_TYPE lsSignal,uint8 *lpData,uint16 liSize),void (*lpHandleConnection)()) : cNetworkBase(liChannels,lpHandlePackets,lpHandleConnection)
{
    mpSync=0;
    mcAddress.host = ENET_HOST_ANY;
    mcAddress.port = liPort;

    mpHost = enet_host_create (& mcAddress,miChannels,2,0,0);
    if (mpHost == NULL)
    {
        TRACE("An error occurred while trying to create an ENet server host.");
    }

//miConnections=0;

}

cP2PHost::~cP2PHost()
{
 delete mpSync;
}


void cP2PHost::HandleConnection()
{

    uint8 Data[sizeof(uint32)+sizeof(uint16)+sizeof(NETWORK_SIGNAL_TYPE)];
    memcpy(Data,&cPacketCodes::SetPeerID,sizeof(NETWORK_SIGNAL_TYPE));
    {
        uint16 liTemp=miPeers+1;
        memcpy(&Data[sizeof(NETWORK_SIGNAL_TYPE)],&liTemp,sizeof(uint16));
    }

    ENetPacket * packet = enet_packet_create (Data,sizeof(uint16)+sizeof(NETWORK_SIGNAL_TYPE),ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send (event.peer, 0, packet);

    mpPeers[miPeers]=event.peer;

     for(uint8 liCount=0;liCount<miPeers;++liCount)
            {
                memcpy(Data,&cPacketCodes::AddClient,sizeof(NETWORK_SIGNAL_TYPE));
                memcpy(&Data[sizeof(NETWORK_SIGNAL_TYPE)],&(event.peer->address.host),sizeof(uint32));
                memcpy(&Data[sizeof(NETWORK_SIGNAL_TYPE)+sizeof(uint32)],&(event.peer->address.port),sizeof(uint16));
                Data[sizeof(uint32)+sizeof(uint16)+sizeof(NETWORK_SIGNAL_TYPE)]=0;
                ENetPacket * packet = enet_packet_create (Data,sizeof(uint32)+sizeof(uint16)+sizeof(NETWORK_SIGNAL_TYPE),ENET_PACKET_FLAG_RELIABLE);


                enet_peer_send (&(mpHost->peers[liCount]), 0, packet);

                memcpy(&Data[sizeof(NETWORK_SIGNAL_TYPE)],&(mpPeers[liCount]->address.host),sizeof(uint32));
                memcpy(&Data[sizeof(uint32)+sizeof(NETWORK_SIGNAL_TYPE)],&(mpPeers[liCount]->address.port),sizeof(uint16));
                Data[sizeof(uint32)+sizeof(uint16)+sizeof(NETWORK_SIGNAL_TYPE)]=0;

                packet = enet_packet_create (Data,sizeof(uint32)+sizeof(uint16)+sizeof(NETWORK_SIGNAL_TYPE),ENET_PACKET_FLAG_RELIABLE);
                enet_peer_send (event.peer, 0, packet);


            }
            TRACE("Add Peer To Host "<<event.peer->address.host<<":"<<event.peer->address.port);
            ++miPeers;
            //++miConnections;

    if(mpHandleConnections) mpHandleConnections();
}

void cP2PHost::HandlePacket(NETWORK_SIGNAL_TYPE lsSignal,uint8 *lpData,uint16 liSize)
{
    switch(lsSignal)
    {
        case WT_PACKET_CODE_REQUEST_SYNC:
        {
            if(!mpSync) mpSync=new cNetworkSyncHost(miPeers,mpPeers,0);
            mpSync->PeerCalling(GetPeerID(event.peer));
        }break;

        default :
        {
            if(mpHandlePackets) mpHandlePackets(lsSignal,lpData,liSize);
        }
    };

};

void cP2PHost::SynchStartToSever(void (*lpStartFunction)(void))
{
  if(!mpSync) mpSync=new cNetworkSyncHost(miPeers,mpPeers,lpStartFunction);
  else
  {
      mpSync->StartFunction(lpStartFunction);
      mpSync->CheckSync();
  }
};

void cNetworkSyncHost::CheckSync()
{
    if(mpStartFunction)
    {
        for(uint16 liCount=0;liCount<miPeers;++liCount)
        {
            if(!mbState[liCount]) return;
        }
        SendZeroSynch();
    }
};


cNetworkSyncHost::cNetworkSyncHost(uint16 liPeers,ENetPeer **lpPeers,void (*lpStartFunction)(void))
{
    mpPeers=lpPeers;
    mpStartFunction=lpStartFunction;
    mbState=new bool[liPeers];
    miPeers=liPeers;
};
cNetworkSyncHost::~cNetworkSyncHost()
{
    delete []mbState;
};

void cNetworkSyncHost::PeerCalling(uint16 liPeer)
{
    mbState[liPeer]=true;
    CheckSync();
};

void cNetworkSyncHost::SendZeroSynch()
{
    uint16 liOffset=0;

    uint16 mpOrder[miPeers];

    for(uint16 liCount=0;liCount<miPeers;++liCount)
    {
        mpOrder[liCount]=liCount;
    }
    bool lbRepeat=true;
    while(lbRepeat && liOffset<miPeers)
    {
        lbRepeat=false;
        uint32 liPing=0;
        uint16 liItem=0;
        for(uint16 liCount=liOffset;liCount<miPeers;++liCount)
        {
            if(mpPeers[liCount]->roundTripTime>liPing)
            {
                liItem=liCount;
                liPing=mpPeers[liCount]->roundTripTime;
                lbRepeat=true;
            }
        }

        liPing=mpOrder[liOffset];
        mpOrder[liOffset++]=mpOrder[liItem];
        mpOrder[liItem]=liPing;
    }


ENetPacket * packet = enet_packet_create ((uint8*)&cPacketCodes::SyncStart,sizeof(NETWORK_SIGNAL_TYPE),ENET_PACKET_FLAG_RELIABLE);
enet_peer_send (mpPeers[mpOrder[0]], 0, packet);
    for(uint16 liCount=1;liCount<miPeers;++liCount)
    {
        gpTimer->SleepWrap((mpPeers[mpOrder[liCount-1]]->roundTripTime-mpPeers[mpOrder[liCount]]->roundTripTime)*0.5);
        enet_peer_send (mpPeers[mpOrder[liCount]], 0, packet);
    }

    gpTimer->SleepWrap((mpPeers[mpOrder[miPeers-1]]->roundTripTime)*0.5);
    mpStartFunction();

};


void cNetworkSyncHost::StartFunction(void (*lpStartFunction)(void))
{
    mpStartFunction=lpStartFunction;
};
