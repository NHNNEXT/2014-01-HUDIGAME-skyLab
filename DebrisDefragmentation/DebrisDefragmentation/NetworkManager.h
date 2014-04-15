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

	static void HandleLoginResult( DDPacketHeader& pktBase );
	static void HandleAccelerationResult( DDPacketHeader& pktBase );
	static void HandleStopResult( DDPacketHeader& pktBase );
	static void HandleRotationResult( DDPacketHeader& pktBase );
	static void HandleSyncResult( DDPacketHeader& pktBase );

private:
	int m_MyPlayerId = -1;
};

extern NetworkManager* GNetworkManger;