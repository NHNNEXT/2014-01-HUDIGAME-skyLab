#pragma once

struct DDPacketHeader;

class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();

	void Init();
	void Connect();
	void Disconnect();

	void SendAcceleration();
	void SendStop();
	void SendTurnBody();
	void SendSkillPush();
	void SendSkillPull();

	int GetMyPlayerId() const { return m_MyPlayerId; }
	void SetMyPlayerId( int val ) { m_MyPlayerId = val; }

	void RegisterHandles();

	static void HandleLoginResult( DDPacketHeader& pktBase );
	static void HandleSyncResult( DDPacketHeader& pktBase );

	static void HandleGoForwardResult( DDPacketHeader& pktBase );
	static void HandleStopResult( DDPacketHeader& pktBase );
	static void HandleTurnBodyResult( DDPacketHeader& pktBase );
	
	static void HandlePushResult( DDPacketHeader& pktBase );
	static void HandlePullResult( DDPacketHeader& pktBase );

private:
	static int m_MyPlayerId;
	
};

extern NetworkManager* GNetworkManager;