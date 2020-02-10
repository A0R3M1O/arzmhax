#include "main.h"
#include "util/armhook.h"
#include "sa.h"
#include "samp.h"

extern ARMHook *pARMHook;

bool bGameStarted = false;
void InstallPatchesInGame();

void (*Render2dStuff)();
void Render2dStuff_hook()
{
	if(!bGameStarted)
	{
		InstallPatchesInGame();
		InstallSAHooksInGame();
		InstallSAMPHooksInGame();

		bGameStarted = true;
	}

	Render2dStuff();
}

void InstallSAHooksInGame()
{
	// todo
}

void InstallSAHooks()
{
	LOGI("SA install hooks..");

	// pARMHook->installHook(g_libGTASA + 0x003F641C, (uintptr_t)Render2dStuff_hook, (uintptr_t*)&Render2dStuff, true);
}
