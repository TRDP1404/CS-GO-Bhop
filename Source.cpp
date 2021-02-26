#include "functions.h"

#define wEntityList = 0x4DA2F44;
#define forcejump = 0x524CEA4;
#define m_fFlags = 0x104;
#define m_iHealth = 0x100;


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
		
	while (true)
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
