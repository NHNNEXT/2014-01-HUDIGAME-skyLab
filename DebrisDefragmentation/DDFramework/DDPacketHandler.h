#pragma once

#include "DDCircularBuffer.h"
#include "DDPacketHeader.h"

class DDPacketHandler
{
public:
	DDPacketHandler( ){}
	virtual ~DDPacketHandler( ){}

	virtual void HandlingPacket( short packetType, DDCircularBuffer* circularBuffer, DDPacketHeader* header ) = 0;
};