#pragma once

// raknet
#include "vendor/RakNet/RakClient.h"
#include "vendor/RakNet/NetworkTypes.h"
#include "vendor/RakNet/BitStream.h"
#include "vendor/RakNet/RakClientInterface.h"
#include "vendor/RakNet/RakNetworkFactory.h"
#include "vendor/RakNet/PacketEnumerations.h"
#include "vendor/RakNet/StringCompressor.h"

class CHookedRakClientInterface
{
public:
	CHookedRakClientInterface();
	~CHookedRakClientInterface();

	bool RPC(int* uniqueID, RakNet::BitStream *parameters, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp);
	bool Send(RakNet::BitStream * bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel);
	Packet* Receive(void);

	bool Connect(const char* host, unsigned short serverPort, unsigned short clientPort, unsigned int depreciated, int threadSleepTimer);
	void Disconnect(unsigned int blockDuration, unsigned char orderingChannel);

public:
	RakClientInterface* m_pHookedRakClient;
};

BYTE GetPacketID(Packet *p);