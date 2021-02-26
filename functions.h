#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include "offsets.h"
uintptr_t moduleBase;
DWORD procId;
HWND hwnd;
HANDLE hProc;

uintptr_t GetModuleBaseAddress(const char* modName) {
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	if (hSnap != INVALID_HANDLE_VALUE) {
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry)) {
			do {
				if (!strcmp(modEntry.szModule, modName)) {
					CloseHandle(hSnap);
					return (uintptr_t)modEntry.modBaseAddr;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	return 0;
}

template<typename T> T RPM(SIZE_T address) {
	T newValue;
	ReadProcessMemory(hProc, (LPCVOID)address, &newValue, sizeof(T), NULL);
	return newValue;
}

template<typename T> void WPM(SIZE_T address, T newValue) {
	WriteProcessMemory(hProc, (LPVOID)address, &newValue, sizeof(newValue), NULL);
}

uintptr_t localPlayer = moduleBase + 0xD8B2BC;

bool healthCheck()
{
	int health = RPM<int>(moduleBase + 0x100);
	if (health < 1)
	{
		return false;
	}
	if (health > 1)
	{
		return true;
	}
}

int i = 0;

void coolLoading()
{
	while (i++ < 4)
	{
		std::ostream& o = (std::cout << "Loading...\n");
		Sleep(500);
	}
}
