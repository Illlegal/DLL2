// dllmain.cpp : Definiuje punkt wejścia dla aplikacji DLL.
#include "pch.h"
#include "Globals.h"
#include "GameFunctions.h"
//#include "GameFunctionsCustom.h"
#include "AddressGathering.h"
using namespace std;

bool active_waithack = false;
bool active_nostun = false;

void BackgroundTask() {  
    while (true) { 
        if (GetAsyncKeyState(VK_INSERT) & 1) {
            active_waithack = !active_waithack;
            cout << ".WaitHack " << (active_waithack ? "Activated" : "Deactivated") << endl;
        }
        if (GetAsyncKeyState(VK_HOME) & 1) {
            Sleep(30);
        }
        if (GetAsyncKeyState(VK_SHIFT) & 1)
        {
            active_nostun = !active_nostun;
            cout << ".NoStun " << (active_nostun ? "Activated" : "Deactivated") << endl; //NIE DZIAŁA!
        }
        if (GetAsyncKeyState(VK_MENU) & 1)//ALT
        {
            Sleep(10);
        }
        if (active_waithack == true) {

            Sleep(50);
        }
        if (active_nostun == true){
            //GameFunctions::UseSkill(0x5E);
            cout << Globals::SendUseSkillPacket << endl;
            cout << GameFunctions::c_funcs::Instance().f_SendUseSkillPacket << endl;
            cout << GameFunctions::c_funcs::Instance().NetPointer << endl;
            Sleep(10);
        }
    }    
}

//Główna funkcja
#pragma optimize("", off)
void HookThread(const HMODULE instance) {
    volatile int bogus = 0;
    while (bogus != 5) {
        if (bogus == 7) {
            FreeLibraryAndExitThread(instance, 0);
        }
        switch (bogus) {
        case 0: {
            bogus = 1;
            break;
        }
        case 1:
        {
            LI_FN(AllocConsole)();
            FILE* f;
            freopen_s(&f, xorstr_("CONOUT$"), "w", stdout);
            cout << "Injected\n1" << std::endl;
            uintptr_t moduleBase = (uintptr_t)LI_FN(GetModuleHandleA)((xorstr_("PolandMT2.exe")));//GetModuleHandleW(L"PolandMT2.exe"); //xorstr_("PolandMT2.exe")
            volatile uintptr_t meltedBase = moduleBase;
            cout << "ModuleBase: " << std::hex << moduleBase <<std::endl;
            Utility::GetAddies();
            GameFunctions::SetAddies();
            GameFunctions::HookToGetNetPointer();
            thread(BackgroundTask).detach();

            // Junk code
            volatile int junkVar = 123;
            junkVar += 456;
            if (junkVar == 579) {
                junkVar *= 2;
            }
            else {
                junkVar /= 2;
            }
            //thread(BackgroundTask).detach();
            bogus = 4;
            break;
        }
        case 2: {
            // Dead code
            int deadVar1 = 10;
            int deadVar2 = 20;
            int deadResult = deadVar1 + deadVar2;
            if (deadResult == 30) {
                deadResult *= 2;
            }
            else {
                deadResult /= 2;
            }
            bogus = 5;
            break;
        }
        case 3: {
            // More dead code
            for (int i = 0; i < 5; i++) {
                int deadLoopVar = i * 10;
                deadLoopVar += 5;
            }
            bogus = 5;
            break;
        }
        case 4:
        default: {
            bogus = 5;
            break;
        }
        if (bogus == 5) {
        volatile int fakeLoop = 0;
        while (fakeLoop < 3) {
        fakeLoop++;
        }

        // More junk code
        for (int i = 0; i < 5; i++) {
         int junkLoopVar = i * 2;
        junkLoopVar += 1;
        }

        // Another layer of dead code
        int deadCodeVar1 = 100;
        int deadCodeVar2 = 200;
        int deadCodeResult = deadCodeVar1 + deadCodeVar2;
        if (deadCodeResult == 300) {
        deadCodeResult -= 50;
        }
        else {
        deadCodeResult += 50;
        }
        
        }
        }
    }
}
#pragma optimize("", on)

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        HookThread(hModule);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}