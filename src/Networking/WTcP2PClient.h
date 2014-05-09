#ifndef __WTCP2PCLIENT_H__
#define __WTCP2PCLIENT_H__

class cNetworkSyncClient
{
    friend class cP2PClient;
    void (*mpStartFunction)(void);
public:

    cNetworkSyncClient(ENetPeer *lpPeer,void (*lpStartFunction)(void));
    ~cNetworkSyncClient();
    void StartFunction(void (*lpStartFunction)(void));
    void Start();

};

class cP2PClient : public cNetworkBase
{
    cNetworkSyncClient *mpSync;
    void StartConnection(uint16 liChannels,void (*lpHandlePackets)(NETWORK_SIGNAL_TYPE lsSignal,uint8 *lpData,uint16 liSize),void (*lpHandleConnection)());
public:
    cP2PClient(string lsAddress,uint16 liPort,uint16 liChannels=16,void (*lpHandlePackets)(NETWORK_SIGNAL_TYPE lsSignal,uint8 *lpData,uint16 liSize)=0,void (*lpHandleConnection)()=0);
    cP2PClient(ENetAddress &lcAddress,uint16 liChannels=16,void (*lpHandlePackets)(NETWORK_SIGNAL_TYPE lsSignal,uint8 *lpData,uint16 liSize)=0,void (*lpHandleConnection)()=0);
    ~cP2PClient();
    void HandleConnection();
    void HandlePacket(NETWORK_SIGNAL_TYPE lsSignal,uint8 *lpData,uint16 liSize);
    void SynchStartToSever(void (*lpStartFunction)(void));


};


#endif
