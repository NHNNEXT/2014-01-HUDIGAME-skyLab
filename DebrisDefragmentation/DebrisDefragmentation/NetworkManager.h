#pragma once
class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();

	void SendAcceleration();
	void SendStop();
	void SendRotation( double y, double x );

private:
	int m_MyPlayerId = -1;
};

extern NetworkManager* GNetworkManger;