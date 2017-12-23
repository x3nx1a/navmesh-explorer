#include <Windows.h>
#include <cstdio>

#include "hook.h"
#include "Client.h"

#include "sdk\gfx\GFX3DFunction\GFXVideo3d.h"

HINSTANCE dllInstance;
HMODULE sro_client = 0;

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD fdwReason, LPVOID lpReserved) {
	
	if (fdwReason == DLL_PROCESS_ATTACH) {
		replaceOffset(0x00B49AE4, (int)&_FakeWinMain);

		replaceAddr(0x00E096A4, addr_from_this(&CGFXVideo3d::EndSceneIMPL));

		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		freopen("CONIN$", "r", stdin);

		printf("florian0's dev-client\n");
		
		dllInstance = hModule;
		printf("hModule = 0x%08x\n", dllInstance);
	} else if (fdwReason == DLL_PROCESS_DETACH) {
		
	}

	return TRUE;
}
