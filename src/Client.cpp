#include <Windows.h>
#include <stdio.h>
#include <string>

#include "Client.h"

#include "hook.h"

#include "sdk/gfx/GFX3DFunction/GFXVideo3d.h"
#include "sdk/gfx/imgui/imgui.h"
#include "sdk/gfx/imgui/imgui_impl_dx9.h"
#include "engine/CMsgHooker.h"
#include "Debug.h"
#include "engine/Game.h"

#pragma comment(lib, "winmm.lib")

extern HINSTANCE dllInstance;

extern LRESULT ImGui_ImplDX9_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

WNDPROC g_WndProc = (WNDPROC)0x008311C0;
#define g_CGInterface (void*)0x0110F80C

CMsgHooker **g_pCMsgHooker = (CMsgHooker**)0x00EECD4C;

#define MAX_LOADSTRING 100

#define szTitle ((LPSTR)0x00EECCB0)
#define szWindowClass ((LPSTR)0x00EECC48)

void MyDebugCallback(char *message);
void InitTimestamp();

int* g_currentTime = (int*)0x0110F800;

DWORD g_startTime = 0;

int APIENTRY _FakeWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	MSG msg;
	HACCEL hAccelTable;

	g_startTime = timeGetTime();

	RegisterDebugCallback(&MyDebugCallback);

	//replaceAddr(0x00EC2FC0, addr_from_this(&CPSCharacterSelect::OnCreateButton_Click));

	DebugPrint("Starting Custom WinMain\n");

	if ( *(int*)0xEECC14 )
		reinterpret_cast<void (*)(int, int)>(0x49E450)(0x512, 0x52A);
	else
		reinterpret_cast<void (*)(int, int)>(0x49E450)(0x512, 0x501);

	LoadString(hInstance, 0x67, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, 0x6D, szWindowClass, MAX_LOADSTRING);

	// Show the client, if its already open
	CreateMutex(0, 0, "Silkroad Client");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		HWND hwnd = FindWindow(szWindowClass, szTitle);
		if (hwnd)
			SetForegroundWindow(hwnd);

		return 0;
	}

	// Setup random
	srand(timeGetTime());

	// CheckLauncherMutex(); // obsolete

	g_CGame->InitGameAssets();

	// sub_56E040(); returns 1

	//if ( g_CMsgHooker )
	//	g_CMsgHooker->field_0();


	reinterpret_cast<void (*)(HINSTANCE)>(0x00831310)(hInstance);
	// MyRegisterClass(hInstance);

	
	// InitInstance(hInstance, nCmdShow)
	if (!reinterpret_cast<int (*)(HINSTANCE,int)>(0x00831060)(hInstance, nCmdShow)) {
		return FALSE;
	}

	g_CGame->F8(0);

	// Register Hotkeys
	if (!(*((int*)0xEECC18)))
	{
		RegisterHotKey(g_CGame->hwnd(), 0, 1, VK_RETURN);
		RegisterHotKey(g_CGame->hwnd(), 2, 1, VK_F4);

	}

	ImGui_ImplDX9_Init(g_CGame->hwnd(), CGFXVideo3d::get()->m_pd3dDevice );

	// Main message loop:
	while (true) {
		while (!PeekMessage(&msg, NULL, 0, 0, 0)) {
			g_CGame->Cycle();
		}

		if (!GetMessage(&msg, NULL, 0, 0))
			break;

		// Pass event to ImGui
		ImGui_ImplDX9_WndProcHandler(g_CGame->hwnd(), msg.message, msg.wParam, msg.lParam);

		// Block input if window is active
		if (ImGui::IsMouseHoveringAnyWindow())
			continue;

		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			if ((*((int*)0xEECC14)) || GetKeyState(VK_MENU) >= 0 || msg.wParam != 9) // TODO: What is 9 ??
			{
				if (msg.wParam != 18) { // TODO: What is 18 ?
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}

			if (msg.message != WM_KEYFIRST && msg.message != WM_KEYUP && msg.message != WM_CHAR && msg.message != WM_SYSKEYDOWN && msg.message != WM_SYSKEYUP) 
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}

	// TODO: Cleanup
	g_CGame->SetNextProcess(NULL);
	// g_CMemPoolManager->Cleanup();

	return (int) msg.wParam;
}

void MyDebugCallback(char *message) {
	printf("[%9.3lf] %s", (timeGetTime() - g_startTime) / (double)1000.0, message);
}

void InitTimestamp() {
	*g_currentTime = timeGetTime();
}
