#include "functions.h"

int main()
{

	system("color 71");
	coolLoading();
	hwnd = FindWindowA(NULL, "Counter-Strike: Global Offensive");
	GetWindowThreadProcessId(hwnd, &procId);
	moduleBase = GetModuleBaseAddress("client.dll");
	hProc = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
	
	int forceJumpValue = 0;
	printf("Cheat Loaded!\n");
		
	while (GetAsyncKeyState(VK_END))
	{
		uintptr_t localPlayer = RPM<uintptr_t>(moduleBase + 0x4DA2F44);
		int flags = RPM<int>(localPlayer + 0x104);
		if (flags & 1) {
			forceJumpValue = 5;
		}
		else {
			forceJumpValue = 4;
		}

		if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
			WPM(moduleBase + 0x524CEA4, forceJumpValue);
		}
	}
}
