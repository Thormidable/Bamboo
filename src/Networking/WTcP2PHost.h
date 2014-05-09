#ifndef __WTCP2PHOST_H__
#define __WTCP2PHOST_H__

class cNetworkSyncHost
{
    friend class cP2PHost;
    bool *mbState;
    ENetPeer **mpPeers;
    uint16 miPeers;
    void (*mpStartFunction)(void);
public:

    cNetworkSyncHost(uint16 liPeers,ENetPeer **lpPeers,void (*lpStartFunction)(void));
    ~cNetworkSyncHost();
    void PeerCalling(uint16 liPeer);
    void SendZeroSynch();
    void StartFunction(void (*lpStartFunction)(void));
    void CheckSync();

};


class cP2PHost : public cNetworkBase
{
    cNetworkSyncHost *mpSync;
public:
    cP2PHost(uint16 liPort,uint16 liChannels=16,void (*lpHandlePackets)(NETWORK_SIGNAL_TYPE lsSignal,uint8 *lpData,uint16 liSize)=0,void (*lpHandleConnection)()=0);
    ~cP2PHost();
    void HandleConnection();
    void HandlePacket(NETWORK_SIGNAL_TYPE lsSignal,uint8 *lpData,uint16 liSize);
    void SynchStartToSever(void (*lpStartFunction)(void));
};

#endif
