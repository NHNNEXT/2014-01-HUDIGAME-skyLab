#pragma once

#include "DDConfig.h"
#include "DDCircularBuffer.h"
#include "DDPacketHandler.h"
#include <map>

#define MAX_LOADSTRING 100

#define IDC_SEND_BUTTON	103
#define WM_SOCKET		104

#define BUFSIZE	1024*10

typedef void( *HandlerFunc )( DDPacketHeader& pktBase );

class DDNetwork : public Singleton<DDNetwork>
{
public:
	friend class DDApplication;

	DDNetwork();
	~DDNetwork();

	bool Release();

	bool Init( );
	bool Connect( const char* serverIP, int port );
	void Disconnect();

	void SetPacketHandler( short packetType, DDPacketHandler* handler );

	void Write( const char* data, size_t size );
	void Read( );

	void RegisterHandler( int pktType, HandlerFunc handler );
	static void DefaultHandler( DDPacketHeader& pktBase );

	void HandleInit();

private:
	void ProcessPacket( );

	SOCKET m_Socket;

	SOCKADDR_IN m_ServerAddr;

	DDCircularBuffer m_RecvBuffer;
	DDCircularBuffer m_SendBuffer;

	// packet handle
	// 조심해! 하드코딩
	HandlerFunc m_HandlerTable[1024];
};