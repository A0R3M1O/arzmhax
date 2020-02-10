#include "main.h"
#include "HookedRakNet.h"
#include "util/armhook.h"

extern ARMHook *pARMHook;
extern CHookedRakClientInterface *pHookedRakClientInterface;

RakClientInterface* (*RakNetworkFactory__GetRakClientInterface)();
RakClientInterface* RakNetworkFactory__GetRakClientInterface_hook()
{
	pHookedRakClientInterface->m_pHookedRakClient = RakNetworkFactory__GetRakClientInterface();

	return (RakClientInterface*)pHookedRakClientInterface->m_pHookedRakClient;
}

CHookedRakClientInterface::CHookedRakClientInterface()
{
	LOGI("CHookedRakClientInterface :: install hooks..");
	
	// pARMHook->installHook(g_libSAMP + 0x000BFDD4, (uintptr_t)RakNetworkFactory__GetRakClientInterface_hook, (uintptr_t*)&RakNetworkFactory__GetRakClientInterface, false);
}

bool CHookedRakClientInterface::RPC(int* uniqueID, RakNet::BitStream *parameters, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp)
{
	if(!m_pHookedRakClient) return false;

	// todo
	return true;
}

bool CHookedRakClientInterface::Send(RakNet::BitStream * bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel)
{
	if(!m_pHookedRakClient) return false;

	// todo
	return true;
}

Packet* CHookedRakClientInterface::Receive(void)
{
	if(!m_pHookedRakClient) return nullptr;

	// todo
	return nullptr;
}

bool CHookedRakClientInterface::Connect(const char* host, unsigned short serverPort, unsigned short clientPort, unsigned int depreciated, int threadSleepTimer)
{
	if(!m_pHookedRakClient) return false;

	return m_pHookedRakClient->Connect(host, serverPort, clientPort, depreciated, threadSleepTimer);
}

void CHookedRakClientInterface::Disconnect(unsigned int blockDuration, unsigned char orderingChannel)
{
	if(m_pHookedRakClient)
		m_pHookedRakClient->Disconnect(blockDuration, orderingChannel);
}

bool CHookedRakClientInterface::SetMTUSize(int size)
{
	if(!m_pHookedRakClient) return false;

	return m_pHookedRakClient->SetMTUSize(size);
}

BYTE GetPacketID(Packet *p)
{
	if(p == 0) 
		return 255;

	return (unsigned char)p->data[0];
}