#include "main.h"
#include "util/gtahook.h"
#include "sa.h"
#include "samp.h"

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
	// GTAHook_SetUpHook(g_libGTASA + 0x003F641C, (uintptr_t)Render2dStuff_hook, (uintptr_t*)&Render2dStuff);

	// wtf
}
