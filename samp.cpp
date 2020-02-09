#include "main.h"
#include "util/samphook.h"
#include "settings.h"
#include "HookedRakNet.h"

extern CSettings *pSettings;

CHookedRakClientInterface *pHookedRakClientInterface = nullptr;

void InstallSAMPHooksInGame()
{
	// todo
}

void InstallSAMPHooks()
{
	// raknet hook
	pHookedRakClientInterface = new CHookedRakClientInterface();
}