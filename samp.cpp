#include "main.h"
#include "settings.h"
#include "util/armhook.h"
#include "HookedRakNet.h"

extern CSettings *pSettings;
extern ARMHook *pARMHook;

CHookedRakClientInterface *pHookedRakClientInterface = nullptr;

void InstallSAMPHooksInGame()
{
	// todo
}

void InstallSAMPHooks()
{
	LOGI("SA-MP install hooks..");

	// raknet hook
	pHookedRakClientInterface = new CHookedRakClientInterface();
}