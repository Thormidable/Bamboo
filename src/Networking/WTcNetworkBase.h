#ifndef __WTCNETWORKBASE_H__
#define __WTCNETWORKBASE_H__

class cNetworkBase : public cFrameUpdateType
{
protected:

    ENetEvent event;

    ENetAddress mcAddress;
    ENetHost *mpHost;

    ENetPeer **mpPeers;
    uint16 miPeers;

    uint16 miThisPeerID;
    uint16 miChannels;
    //uint16 miConnections;
    void (*mpHandlePackets)(NETWORK_SIGNAL_TYPE lsSignal,uint8 *lpData,uint16 liSize);
    void (*mpHandleConnections)();

    virtual void HandleConnection()=0;
    virtual void HandlePacket(NETWORK_SIGNAL_TYPE lsSignal,uint8 *lpData,uint16 liSize)=0;
    void Flush();
    void ReceivePackets();
    void HandleDisconnect(ENetPeer *lcPeer);

    static cNetworkBase *mpInstance;
    cNetworkBase(uint16 liChannels=16,void (*lpHandlePackets)(NETWORK_SIGNAL_TYPE lsSignal,uint8 *lpData,uint16 liSize)=0,void (*lpHandleConnections)()=0);

public:

    ~cNetworkBase();
    static cNetworkBase* Instance();


    void SendSignal(NETWORK_SIGNAL_TYPE Signal);
    void SendSignal(NETWORK_SIGNAL_TYPE Signal,uint16 liPeerTarget);

    template<class tType> static void SendPacket(NETWORK_SIGNAL_TYPE Signal,tType *lpSignal,uint16 liSize);
    template<class tType> static void SendPacket(tType *lpData,uint16 liSize);

    template<class tType> static void SendPacket(NETWORK_SIGNAL_TYPE Signal,tType *lpSignal,uint16 liSize,uint16 liPeerTarget);
    template<class tType> static void SendPacket(tType *lpData,uint16 liSize,uint16 liPeerTarget);

    void SendPacketLocal(NETWORK_SIGNAL_TYPE Signal, uint8 *lpSignal,uint16 liSize);
    void SendPacketLocal(uint8 *lpData,uint16 liSize);
    void SendPacketLocal(NETWORK_SIGNAL_TYPE Signal, uint8 *lpSignal,uint16 liSize,uint16 liPeerTarget);
    void SendPacketLocal(uint8 *lpData,uint16 liSize,uint16 liPeerTarget);

    static cNetworkBase *GetP2PServer(uint16 liPort,uint16 liChannels=16,void (*lpHandlePackets)(NETWORK_SIGNAL_TYPE lsSignal,uint8 *lpData,uint16 liSize)=0,void (*lpHandleConnections)()=0);
    static cNetworkBase *GetP2PClient(string lsAddress,uint16 liPort,uint16 liChannels=16,void (*lpHandlePackets)(NETWORK_SIGNAL_TYPE lsSignal,uint8 *lpData,uint16 liSize)=0,void (*lpHandleConnections)()=0);
    static cNetworkBase *GetP2PClient(ENetAddress &lcAddress,uint16 liChannels=16,void (*lpHandlePackets)(NETWORK_SIGNAL_TYPE lsSignal,uint8 *lpData,uint16 liSize)=0,void (*lpHandleConnections)()=0);

    virtual void SynchStartToSever(void (*lpStartFunction)(void))=0;

    void Disconnect();

    void FrameUpdate();

    uint16 Peers();
    uint16 GetPeerID(ENetPeer *lpPeer);
    uint16 GetEventPeerID();

    uint16 PeerID();

    void SetHandlePacketFunction(void (*lpHandlePackets)(NETWORK_SIGNAL_TYPE lsSignal,uint8 *lpData,uint16 liSize));
    void SetHandleConnectionFunction(void (*lpHandleConnection)());

    static bool sbENetInitialised;
};

template<class tType> void cNetworkBase::SendPacket(NETWORK_SIGNAL_TYPE Signal, tType *lpSignal,uint16 liSize)
{
    if(mpInstance) mpInstance->SendPacketLocal(Signal,(uint8*)lpSignal,liSize);
};
template<class tType> void cNetworkBase::SendPacket(tType *lpData,uint16 liSize)
{
    if(mpInstance) mpInstance->SendPacketLocal((uint8*)lpData,liSize);
};

template<class tType> void cNetworkBase::SendPacket(NETWORK_SIGNAL_TYPE Signal, tType *lpSignal,uint16 liSize,uint16 liPeerTarget)
{
    if(mpInstance) mpInstance->SendPacketLocal(Signal,(uint8*)lpSignal,liSize,liPeerTarget);
};
template<class tType> void cNetworkBase::SendPacket(tType *lpData,uint16 liSize,uint16 liPeerTarget)
{
    if(mpInstance) mpInstance->SendPacketLocal((uint8*)lpData,liSize,liPeerTarget);
};

#endif
