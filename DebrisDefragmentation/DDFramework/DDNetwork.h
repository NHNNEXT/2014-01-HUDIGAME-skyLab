#pragma once

#include "DDConfig.h"
#include "DDCircularBuffer.h"
#include "DDPacketHandler.h"
#include <map>

#define MAX_LOADSTRING 100

#define IDC_SEND_BUTTON	103
#define WM_SOCKET		104

#define BUFSIZE	1024*10

class DDNetwork
{
public:
	friend class DDApplication;

	DDNetwork( );
	~DDNetwork( );

	static void ReleaseInstance( );

	bool Init( );
	void Destroy( );
	bool Connect( const char* serverIP, int port );

	void SetPacketHandler( short packetType, DDPacketHandler* handler );

	void Write( const char* data, size_t size );
	void Read( );

private:
	void ProcessPacket( );

	SOCKET m_Socket;

	SOCKADDR_IN m_ServerAddr;

	DDCircularBuffer m_RecvBuffer;
	DDCircularBuffer m_SendBuffer;

	std::map<short, DDPacketHandler*> m_PacketHandler;


};

extern DDNetwork* GDDNetwork;