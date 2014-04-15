#pragma once

struct DDPacketHeader;

class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();

	void SendAcceleration();
	void SendStop();
	void SendRotation( double y, double x );

	void RegisterHandles();
	void SetMyPlayerId( int id ) { m_MyPlayerId - id; }

	static void HandleLoginResult( DDPacketHeader& pktBase );
	static void HandleAccelerationResult( DDPacketHeader& pktBase );
	static void HandleStopResult( DDPacketHeader& pktBase );
	static void HandleRotationResult( DDPacketHeader& pktBase );
	static void HandleSyncResult( DDPacketHeader& pktBase );

private:
	static int m_MyPlayerId;
};

extern NetworkManager* GNetworkManger;