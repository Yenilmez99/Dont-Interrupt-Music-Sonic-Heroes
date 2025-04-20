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

std::string GetDllPath(std::string DLLName) {
    HMODULE hModule = NULL;
    char path[MAX_PATH];
    std::string DLLPath = "";
    LPCSTR DLLNameLPCSTR = DLLName.c_str();

    GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_PIN, DLLNameLPCSTR, &hModule);
    GetModuleFileNameA(hModule, path, MAX_PATH);
    DLLPath = path;

    if (DLLPath.find_last_of("\\/") != std::string::npos)
        DLLPath = DLLPath.substr(0, DLLPath.find_last_of("\\/"));

    return DLLPath;
}


DWORD WINAPI MainCore(HMODULE hModule) {

    HWND hwnd_SonicHeroesTM = FindWindowA(NULL, "SONIC HEROES(TM)");
    while (hwnd_SonicHeroesTM == NULL)
        hwnd_SonicHeroesTM = FindWindowA(NULL, "SONIC HEROES(TM)");
    DWORD ProcessIDSonicHeroes = NULL;
    GetWindowThreadProcessId(hwnd_SonicHeroesTM, &ProcessIDSonicHeroes);
    HANDLE HandleSonicHeroes = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessIDSonicHeroes);
    char SonicHeroesGameModule[] = "Tsonic_win.exe";
    DWORD SonicHeroesMainAdress = GetModuleBaseAddress(_T(SonicHeroesGameModule), ProcessIDSonicHeroes);

    bool StageOpen = 0;
    uint8_t SelectedTeam = 0;
    uint8_t MusicEdit = 0;
    UINT8 SelectedStage = 0;

    std::ifstream File(GetDllPath("Dont Interrupt Music (SH).dll") + "\\..\\..\\User\\Mods\\sonicheroes.musicedit.dontinterruptmusicsh\\Config.json");
    nlohmann::json ConfigData;
    File >> ConfigData;

    bool ReadCharacterConfig[4] = { 1,1,0,0 };
    bool ReadStageConfig[23];

    for (short u = 0; u < 23; u++) {
        if (u == 10 || u == 11)
            ReadStageConfig[u] = 0;
        else
            ReadStageConfig[u] = 1;
    }

    if (!File.is_open()) {
        std::cout << "Proje acilamadi";
    }
    else {
        ReadCharacterConfig[0] = ConfigData["TeamSonic"];
        ReadCharacterConfig[1] = ConfigData["TeamDark"];
        ReadCharacterConfig[2] = ConfigData["TeamRose"];
        ReadCharacterConfig[3] = ConfigData["TeamChaotix"];

        ReadStageConfig[0] = ConfigData["SeasideHill"];
        ReadStageConfig[1] = ConfigData["OceanPlace"];
        ReadStageConfig[2] = ConfigData["GrandMetropolis"];
        ReadStageConfig[3] = ConfigData["PowerPlant"];
        ReadStageConfig[4] = ConfigData["CasinoPark"];
        ReadStageConfig[5] = ConfigData["BingoHighway"];
        ReadStageConfig[6] = ConfigData["RailCanyon"];
        ReadStageConfig[7] = ConfigData["BulletStation"];
        ReadStageConfig[8] = ConfigData["FrogForest"];
        ReadStageConfig[9] = ConfigData["LostJungle"];
        ReadStageConfig[10] = ConfigData["HangCastle"];
        ReadStageConfig[11] = ConfigData["MysticMansion"];
        ReadStageConfig[12] = ConfigData["EggFleet"];
        ReadStageConfig[13] = ConfigData["FinalFortress"];
        ReadStageConfig[14] = ConfigData["EGGHAWK"];
        ReadStageConfig[15] = ConfigData["TEAMVS1"];
        ReadStageConfig[16] = ConfigData["ROBOTCARNIVAL"];
        ReadStageConfig[17] = ConfigData["EGGALBATROS"];
        ReadStageConfig[18] = ConfigData["TEAMVS2"];
        ReadStageConfig[19] = ConfigData["ROBOTSTORM"];
        ReadStageConfig[20] = ConfigData["EGGEMPEROR"];
        ReadStageConfig[21] = ConfigData["METALMADNESS"];
        ReadStageConfig[22] = ConfigData["METALSONIC"];
    }
    File.close();

    DWORD MusicEditMainAdress = 0x006778A0;
    std::vector<DWORD> MusicEditOffset{ 0x18,0x29 };
    DWORD MusicEditAdress;

    while (true) {
        MusicEditAdress = GetPointerAddress(hwnd_SonicHeroesTM, SonicHeroesMainAdress, MusicEditMainAdress, MusicEditOffset);
        ReadProcessMemory(HandleSonicHeroes, (PBYTE*)MusicEditAdress, &MusicEdit, sizeof(uint8_t), 0);
        ReadProcessMemory(HandleSonicHeroes, (PBYTE*)0x007C6BD4, &StageOpen, sizeof(bool), 0);
        ReadProcessMemory(HandleSonicHeroes, (PBYTE*)0x008D6920, &SelectedTeam, sizeof(uint8_t), 0);
        ReadProcessMemory(HandleSonicHeroes, (PBYTE*)0x008D6720, &SelectedStage, sizeof(uint8_t), 0);
        if (SelectedStage <= 1 || SelectedStage >= 25)
            SelectedStage = 11;
        if (!StageOpen && (MusicEdit == 0x06) && ReadCharacterConfig[SelectedTeam] && ReadStageConfig[SelectedStage - 2]) {
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

