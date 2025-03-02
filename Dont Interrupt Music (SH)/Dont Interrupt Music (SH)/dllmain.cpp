#include "pch.h"

DWORD GetModuleBaseAddress(TCHAR* lpszModuleName, DWORD pID) {
    DWORD dwModuleBaseAddress = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pID);
    MODULEENTRY32 ModuleEntry32 = { 0 };
    ModuleEntry32.dwSize = sizeof(MODULEENTRY32);

    if (Module32First(hSnapshot, &ModuleEntry32))
    {
        do {
            if (_tcscmp(ModuleEntry32.szModule, lpszModuleName) == 0)
            {
                dwModuleBaseAddress = (DWORD)ModuleEntry32.modBaseAddr;
                break;
            }
        } while (Module32Next(hSnapshot, &ModuleEntry32));


    }
    CloseHandle(hSnapshot);
    return dwModuleBaseAddress;
}
DWORD GetPointerAddress(HWND hwnd, DWORD gameBaseAddr, DWORD address, std::vector<DWORD> offsets) {
    DWORD pID = NULL;
    GetWindowThreadProcessId(hwnd, &pID);
    HANDLE phandle = NULL;
    phandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
    if (phandle == INVALID_HANDLE_VALUE || phandle == NULL);

    DWORD offset_null = NULL;
    ReadProcessMemory(phandle, (LPVOID*)(gameBaseAddr + address), &offset_null, sizeof(offset_null), 0);
    DWORD pointeraddress = offset_null;
    for (int i = 0; i < offsets.size() - 1; i++)
    {
        ReadProcessMemory(phandle, (LPVOID*)(pointeraddress + offsets.at(i)), &pointeraddress, sizeof(pointeraddress), 0);
    }
    return pointeraddress += offsets.at(offsets.size() - 1);
}

DWORD WINAPI MainCore(HMODULE hModule) {

    HWND hwnd_SonicHeroesTM = FindWindowA(NULL, "SONIC HEROES(TM)");
    while (hwnd_SonicHeroesTM == NULL) {
        hwnd_SonicHeroesTM = FindWindowA(NULL, "SONIC HEROES(TM)");
    }
    DWORD ProcessIDSonicHeroes = NULL;
    GetWindowThreadProcessId(hwnd_SonicHeroesTM, &ProcessIDSonicHeroes);
    HANDLE HandleSonicHeroes = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessIDSonicHeroes);
    char SonicHeroesGameModule[] = "Tsonic_win.exe";
    DWORD SonicHeroesMainAdress = GetModuleBaseAddress(_T(SonicHeroesGameModule), ProcessIDSonicHeroes);

    bool StageOpen = 0;
    uint8_t MusicEdit = 0;

    DWORD MusicEditMainAdress = 0x006778A0;
    std::vector<DWORD> MusicEditOffset{ 0x18,0x29 };
    DWORD MusicEditAdress;

    while (true) {
        MusicEditAdress = GetPointerAddress(hwnd_SonicHeroesTM, SonicHeroesMainAdress, MusicEditMainAdress, MusicEditOffset);
        ReadProcessMemory(HandleSonicHeroes, (PBYTE*)MusicEditAdress, &MusicEdit, sizeof(uint8_t), 0);
        ReadProcessMemory(HandleSonicHeroes, (PBYTE*)0x007C6BD4, &StageOpen, sizeof(bool), 0);
        if (StageOpen == 0 && MusicEdit == 0x06) {
            MusicEdit = 0x2;
            WriteProcessMemory(HandleSonicHeroes, (PBYTE*)MusicEditAdress, &MusicEdit, sizeof(uint8_t), 0);
        }
        Sleep(15);
    }

    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainCore, hModule, 0, nullptr));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

