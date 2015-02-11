

#include "../WTBamboo.h"

bool cNetworkBase::sbENetInitialised=0;

uint16 cNetworkBase::Peers()
{
    return miPeers;
};

void cNetworkBase::SetHandlePacketFunction(void (*lpHandlePackets)(NETWORK_SIGNAL_TYPE lsSignal,uint8 *lpData,uint16 liSize)){mpHandlePackets=lpHandlePackets;};
void cNetworkBase::SetHandleConnectionFunction(void (*lpHandleConnections)()){mpHandleConnections=lpHandleConnections;};

cNetworkBase *cNetworkBase::mpInstance=0;

cNetworkBase::cNetworkBase(uint16 liChannels,void (*lpHandlePackets)(NETWORK_SIGNAL_TYPE lsSignal,uint8 *lpData,uint16 liSize),void (*lpHandleConnections)())
{
    mpHandleConnections=lpHandleConnections;
    if(!sbENetInitialised)
    {
        if(enet_initialize())
        {
            TRACE("Error with ENet");
            _QUIT;
        }
        else
        {
            TRACE("ENET Initialised");
        }
        sbENetInitialised=true;
    }
    miChannels=liChannels;
    mpHandlePackets=lpHandlePackets;
    miPeers=0;
    mpPeers=new ENetPeer*[liChannels];
    miThisPeerID=0;
};

cNetworkBase::~cNetworkBase()
{
    if(mpHost)
    {
        enet_host_destroy(mpHost);
    }
    delete []mpPeers;
    mpInstance=0;
    enet_deinitialize();
};

uint16 cNetworkBase::PeerID()
{
    return miThisPeerID;
};

void cNetworkBase::ReceivePackets()
{


    // Wait up to 1000 milliseconds for an event.
	//printf("Waiting for event...\n");
    while (enet_host_service (mpHost, & event, 0) > 0)
    {
		switch (event.type)
        {
        case ENET_EVENT_TYPE_CONNECT:
        TRACE("ENet Event Type Connection:");
            HandleConnection();
            break;

        case ENET_EVENT_TYPE_RECEIVE:
            HandlePacket(event.packet->data[0],&event.packet->data[sizeof(NETWORK_SIGNAL_TYPE)],event.packet->dataLength-1);
            // Clean up the packet now that we're done using it.
            enet_packet_destroy (event.packet);
            break;

        case ENET_EVENT_TYPE_DISCONNECT:
            TRACE(event.peer -> data << " disconected");
            HandleDisconnect(event.peer);

            event.peer -> data = NULL;
        }
	}
};

uint16 cNetworkBase::GetEventPeerID()
{
 return GetPeerID(event.peer);
};

void cNetworkBase::Flush()
{
    enet_host_flush(mpHost);
};
/*
void cNetworkBase::SendPacket(uint8 *lpData,uint16 liSize)
{
    if(mpInstance) mpInstance->SendPacketLocal(lpData,liSize);
};

void cNetworkBase::SendPacket(NETWORK_SIGNAL_TYPE Signal, uint8 *lpSignal,uint16 liSize)
{
    if(mpInstance) mpInstance->SendPacketLocal(Signal,lpSignal,liSize);
}
*/

void cNetworkBase::SendSignal(NETWORK_SIGNAL_TYPE Signal)
{
    ENetPacket * packet = enet_packet_create (&Signal,sizeof(NETWORK_SIGNAL_TYPE),ENET_PACKET_FLAG_RELIABLE);
    for(uint8 liCount=0;liCount<miPeers;++liCount) enet_peer_send (mpPeers[liCount], 0, packet);
};
void cNetworkBase::SendSignal(NETWORK_SIGNAL_TYPE Signal,uint16 liPeerTarget)
{
    ENetPacket * packet = enet_packet_create (&Signal,sizeof(NETWORK_SIGNAL_TYPE),ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send (mpPeers[liPeerTarget], 0, packet);
};

void cNetworkBase::SendPacketLocal(uint8 *lpData,uint16 liSize)
{
    ENetPacket * packet = enet_packet_create (lpData,liSize + 1,ENET_PACKET_FLAG_RELIABLE);
    for(uint8 liCount=0;liCount<miPeers;++liCount) enet_peer_send (mpPeers[liCount], 0, packet);
};



void cNetworkBase::SendPacketLocal(NETWORK_SIGNAL_TYPE Signal, uint8 *lpSignal,uint16 liSize)
{
    uint8 lpData[liSize+2];
    memcpy(lpData,&Signal,sizeof(NETWORK_SIGNAL_TYPE));
    memcpy(&lpData[sizeof(NETWORK_SIGNAL_TYPE)],lpSignal,sizeof(char)*liSize);
    lpData[liSize+1]=0;
    SendPacket(lpData,liSize+1);
};


void cNetworkBase::SendPacketLocal(uint8 *lpData,uint16 liSize,uint16 liPeerTarget)
{
    ENetPacket * packet = enet_packet_create (lpData,liSize + 1,ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send (mpPeers[liPeerTarget], 0, packet);
};

void cNetworkBase::SendPacketLocal(NETWORK_SIGNAL_TYPE Signal, uint8 *lpSignal,uint16 liSize,uint16 liPeerTarget)
{
    uint8 lpData[liSize+2];
    memcpy(lpData,&Signal,sizeof(NETWORK_SIGNAL_TYPE));
    memcpy(&lpData[sizeof(NETWORK_SIGNAL_TYPE)],lpSignal,sizeof(char)*liSize);
    lpData[liSize+1]=0;
    SendPacket(lpData,liSize+1,liPeerTarget);
};

void cNetworkBase::HandleDisconnect(ENetPeer *lcPeer)
{
    /*
 for(uint16 liCount=0;liCount<miPeers;++liCount)
 {
     if(mpPeers[liCount].host==lcPeer[0].host && mpPeers[liCount].port==lcPeer->port)
     {
         memmove(&mpPeers[liCount],mpPeers[liCount+1],sizeof(ENetPeer*)*miPeers-liCount-1);
         break;
     }
 }*/
--miPeers;

};

cNetworkBase *cNetworkBase::GetP2PServer(uint16 liPort,uint16 liChannels,void (*lpHandlePackets)(uint8 lsSignal,uint8 *lpData,uint16 liSize),void (*lpHandleConnections)())
{
    if(!mpInstance) mpInstance=_CREATE(cP2PHost(liPort,liChannels,lpHandlePackets,lpHandleConnections));
    return mpInstance;
};
cNetworkBase *cNetworkBase::GetP2PClient(string lsAddress,uint16 liPort,uint16 liChannels,void (*lpHandlePackets)(uint8 lsSignal,uint8 *lpData,uint16 liSize),void (*lpHandleConnections)())
{
    if(!mpInstance) mpInstance=_CREATE(cP2PClient(lsAddress,liPort,liChannels,lpHandlePackets,lpHandleConnections));
    return mpInstance;
};

cNetworkBase *cNetworkBase::GetP2PClient(ENetAddress &lcAddress,uint16 liChannels,void (*lpHandlePackets)(uint8 lsSignal,uint8 *lpData,uint16 liSize),void (*lpHandleConnections)())
{
    if(!mpInstance) mpInstance=_CREATE(cP2PClient(lcAddress,liChannels,lpHandlePackets,lpHandleConnections));
    return mpInstance;
};

void cNetworkBase::FrameUpdate()
{
ReceivePackets();
Flush();
}

uint16 cNetworkBase::GetPeerID(ENetPeer *lpPeer)
{
 for(uint16 liCount=0;liCount<miPeers;++liCount)
 {
     if(mpPeers[liCount]->address.host==lpPeer->address.host
        && mpPeers[liCount]->address.port==lpPeer->address.port)
     {
         return liCount;
     }
 }
 return miPeers;
}

cNetworkBase* cNetworkBase::Instance(){return mpInstance;};

void cNetworkBase::Disconnect()
{
    uint32 liTemp=0;
    for(uint16 liCount=0;liCount<miPeers;++liCount)
    {
        enet_peer_disconnect_now(mpPeers[liCount],liTemp);
    }
    enet_host_destroy(mpHost);
};
