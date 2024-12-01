#include "AddressGathering.h"
#include "Globals.h"
#include "Log.h"
enum EnumServerName
{
    PolandMT2 = 1,
    Ervelia,
    Alune
};
EnumServerName ServerName = PolandMT2;//PolandMT2
bool DbgSession = true;
MODULEINFO GetModuleInfo(const char* szModule)
{
    MODULEINFO modInfo = { 0 };
    HMODULE hModule = GetModuleHandle(szModule);
    if (hModule == 0)
        return modInfo;
    GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(MODULEINFO));
    return modInfo;
}
DWORD FindSignature(const char* module, const  char* pattern, const char* mask)
{
    MODULEINFO mInfo = GetModuleInfo(module);

    DWORD base = (DWORD)mInfo.lpBaseOfDll;
    DWORD size = (DWORD)mInfo.SizeOfImage;

    DWORD patternLength = (DWORD)strlen(mask);

    for (DWORD i = 0; i < size - patternLength; i++)
    {
        bool found = true;
        for (DWORD j = 0; j < patternLength; j++)
        {
            found &= mask[j] == '?' || pattern[j] == *(char*)(base + i + j);
        }
        if (found)
            return base + i;

    }
    return NULL;
}

void Utility::GetAddies()
    {
        DWORD dwSeachPattern = 0x0;
        DWORD B_PlayerBase;
        DWORD B_MobBase;
        DWORD B_SendAttackPacket;
        DWORD B_PlayerGetTargetVID;
        g_LogFile.open("debug_log.txt");
        switch (ServerName)
        {
        case PolandMT2://PolandMT2
        {
            //char P_PlayerBase[] = "\x55\x8B\xEC\x8B\x0D\x00\x00\x00\x00\x8D\x49\x04\x8B\x01\x5D";
            //char M_PlayerBase[] = "xxxxx????xxxxxx";
            B_PlayerBase = FindSignature(xorstr_("PolandMT2.exe"),
                "\x55\x8B\xEC\x8B\x0D\x00\x00\x00\x00\x8D\x49\x04\x8B\x01\x5D",
                "xxxxx????xxxxxx");
            Globals::PlayerBase = *(DWORD*)(B_PlayerBase + 0x5);
            Globals::iCPythonCharacterManagerInstance = *(DWORD*)(B_PlayerBase + 0x5);
            if (DbgSession)
                cout << "CPythonCharacterManagerInstance: " << std::hex << Globals::iCPythonCharacterManagerInstance << std::endl;
            LOG("CPythonCharacterManagerInstance: " << std::hex << Globals::iCPythonCharacterManagerInstance);

            //char P_MobBase[] = "\x75\xE2\x8B\x15\x00\x00\x00\x00\x8B\x35\x00\x00\x00\x00\xFF\x75\xFC\x52\x56";
            //char M_MobBase[] = "xxxx????xx????xxxxx";
            B_MobBase = FindSignature(xorstr_("PolandMT2.exe"),
                "\x75\xE2\x8B\x15\x00\x00\x00\x00\x8B\x35\x00\x00\x00\x00\xFF\x75\xFC\x52\x56",
                "xxxx????xx????xxxxx");
            Globals::MobBase = *(DWORD*)(B_MobBase + 0xA);
            if (DbgSession)
                cout << "MobBase: " << std::hex << Globals::MobBase << std::endl;
            LOG("MobBase: " << std::hex << Globals::MobBase);

            //char P_SendAttackPacket[] = { "\x55\x8B\xEC\x83\xEC\x0C\x56\x8B\xF1\xE8\x00\x00\x00\x00\x84\xC0\x75\x04\xFE\xC0\xEB\x43"};
            //char M_SendAttackPacket[] = "xxxxxxxxxx????xxXXXXXX";
            B_SendAttackPacket = FindSignature(xorstr_("PolandMT2.exe"),
                "\x55\x8B\xEC\x83\xEC\x0C\x56\x8B\xF1\xE8\x00\x00\x00\x00\x84\xC0\x75\x04\xFE\xC0\xEB\x43",
                "xxxxxxxxxx????xxXXXXXX");
            //Globals::SendAttackPacket = *(DWORD*)(B_SendAttackPacket);
            Globals::SendAttackPacket = B_SendAttackPacket;
            if (DbgSession)
                cout << "SendAttackPacket: " << std::hex << Globals::SendAttackPacket << std::endl;
            LOG("SendAttackPacket: " << std::hex << Globals::SendAttackPacket);



            //55 8B EC 8B 45 08 89 81 00 00 00 00 5D C2 04 00           30 FB 04 00 
            //char P_PlayerGetTargetVID[] = {"\x55\x8B\xEC\x51\x51\x8B\x45\x08\x56\x89\x45\xF9\x8B\xF1\x8D\x45\xF8\xC6\x45\xF8\x3D"};//  \x81\x30\xFB\x04\x00\x5D
            //char M_PlayerGetTargetVID[] = "xxxxxxxxxxxxxxxxxxxxx";
            B_PlayerGetTargetVID = FindSignature(xorstr_("PolandMT2.exe"),
                "\x55\x8B\xEC\x51\x51\x8B\x45\x08\x56\x89\x45\xF9\x8B\xF1\x8D\x45\xF8\xC6\x45\xF8\x3D",
                "xxxxxxxxxxxxxxxxxxxxx");
            Globals::PlayerGetTargetVID = B_PlayerGetTargetVID; //<-address
            if (DbgSession)
                cout << "PlayerGetTargetVID: " << std::hex << Globals::PlayerGetTargetVID << std::endl;
            LOG("PlayerGetTargetVID: " << std::hex << Globals::PlayerGetTargetVID);

            /*
            DWORD B_MOVETODIRECTION_FUNCTION = FindSignature(xorstr_("PolandMT2.exe"),
                "\x55\x8b\xec\x83\xec\x00\x89\x4d\x00\x8b\x4d\x00\xe8\x00\x00\x00\x00\x0f\xb6\x00\x85\xc0\x74\x00\xb0",
                "xxxxx?xx?xx?x????xx?xxx?x");
    if (DbgSession)
            cout << "MOVETODIRECTION_FUNCTION: " << std::hex << B_MOVETODIRECTION_FUNCTION << endl;

            DWORD B_PYTHONPLAYER_SENDUSESKILL = FindSignature(xorstr_("PolandMT2.exe"),
                "\x55\x8b\xec\x83\xec\x00\x89\x4d\x00\x8b\x45\x00\x6b\xc0\x00\x8b\x4d\x00\x8d\x94\x01\x00\x00\x00\x00\x89\x55\x00\xa1\x00\x00\x00\x00\x89\x45\x00\x8b\x4d",
                "xxxxx?xx?xx?xx?xx?xxx????xx?x????xx?xx");
            if (DbgSession)
                cout << "PYTHONPLAYER_SENDUSESKILL: " << std::hex << B_PYTHONPLAYER_SENDUSESKILL << endl;
    */
            DWORD B_AppendChat = FindSignature(xorstr_("PolandMT2.exe"),
                "\x55\x8B\xEC\x83\xEC\x18\x53\x56\x57\x89\x4D\xF8",// 55 8b ec 83 ec 0c 53 56 57 89 4d f4
                "xxxxx?xxxxx?");//"xxxxx?xxxxx?");
            Globals::AppendChat = B_AppendChat;
            if (DbgSession)
                cout << "AppendChat: " << B_AppendChat << endl;
            LOG("AppendChat: " << B_AppendChat);

            DWORD B_SendChatPacket = FindSignature(xorstr_("PolandMT2.exe"),
                "\x55\x8B\xEC\x53\x56\x57\x8B\xF9\x8B\x0D\x99\x99\x99\x99\xE8\x99\x99\x99\x99\x85\xC0\x0F\x99\x99\x00\x00\x00\x8B\x75\x08\x56\xE8\x99\x99\x99\x99\x59\x85\xC0",
                "xxxxxxxxxx????x????xxx??xxxxxxxx????xxx");//"xxxxx?xxxxx?");
            Globals::SendChatPacket = B_SendChatPacket;
            if (DbgSession)
                cout << "SendChatPacket: " << B_SendChatPacket << endl;
            LOG("SendChatPacket: " << B_SendChatPacket);

            DWORD B_SendUseSkillPacket = FindSignature(xorstr_("PolandMT2.exe"),
                "\x55\x8B\xEC\x83\xEC\x10\xA1\x00\x34\xB9\x02\x33\xC5\x89\x45\xFC\x8B\x45\x08\x89\x45\xF1\x8B\x45\x0C\x56\x89\x45\xF5\x8B\xF1\x8D\x45\xF0\xC6\x45\xF0\x34\x50\x6A\x09\xE8\xE5\x93\x1F\x00\x84\xC0\x75\x0E\xB9\xE4\x40\xAE\x02\xE8\x8A\x73\x1E\x00\x32\xC0\xEB\x07",
                "xxxxxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxxx????x????xxxx");
            Globals::SendUseSkillPacket = B_SendUseSkillPacket;
            if (DbgSession)
                cout << B_SendUseSkillPacket << endl;
            LOG("SendUseSkillPacket: " << B_SendUseSkillPacket);

            DWORD B_GetMainInstancePtr = FindSignature(xorstr_("PolandMT2.exe"),
                "\x8B\x41\x0C\xC3\x55\x8B\xEC\x81\xEC\x04\x01\x00\x00\xA1\x00\x34\xB9\x02",
                "xxxxxxxxxxxxxx????");
            Globals::GetMainInstancePtr = B_GetMainInstancePtr;
            if (DbgSession)
                cout << B_GetMainInstancePtr << endl;
            LOG("GetMainInstancePtr: " << B_GetMainInstancePtr);

            DWORD B_SendShootPacket = FindSignature(xorstr_("PolandMT2.exe"),
                "\x55\x8B\xEC\x83\xEC\x0C\x8A\x45\x08\x56\x8B\xF1\xC6\x45\xF4\x36\x8B\x0D\xC0\x00\xE0\x02\x88\x45\xF5\xE8\x40\x62\xFA\xFF\x89\x45\xFC\x8B\xCE",
                "xxxxxxxxxxxxxxxxxx????xxxx????xxxxx");
            Globals::SendShootPacket = B_SendShootPacket;
            if (DbgSession)
                cout << B_SendShootPacket << endl;
            LOG("SendShootPacket: " << B_SendShootPacket);

            DWORD B_SendAddFlyTargetingPacket = FindSignature(xorstr_("PolandMT2.exe"),
                "\x55\x8B\xEC\x83\xEC\x14\xA1\x00\x34\xB9\x02\x33\xC5\x89\x45\xFC\x8B\x45\x08\x56\x8B\xF1\x89\x45\xED\x8B\x4D\x0C\xC6\x45\xEC\x35\xF3\x0F\x2C\x01\x89\x45\xF1\xF3\x0F\x2C\x41\x04\x89\x45\xF5\x8D\x45\xF5\x50\x8D\x45\xF1\x50\x51",
                "xxxxxxx????xxxxxxxxxxxxxxxxxxxxxx???xxxx????xxxxxxxxxxxx");
            Globals::SendAddFlyTargetingPacket = B_SendAddFlyTargetingPacket;
            if (DbgSession)
                cout << B_SendAddFlyTargetingPacket << endl;
            LOG("SendAddFlyTargetingPacket: " << B_SendAddFlyTargetingPacket);

            DWORD B_SendFlyTargetingPacket = FindSignature(xorstr_("PolandMT2.exe"),
                "\x55\x8B\xEC\x83\xEC\x14\xA1\x00\x34\xB9\x02\x33\xC5\x89\x45\xFC\x8B\x45\x08\x56\x8B\xF1\x89\x45\xED\x8B\x4D\x0C\xC6\x45\xEC\x33\xF3\x0F\x2C\x01\x89\x45\xF1\xF3\x0F\x2C\x41\x04\x89\x45\xF5\x8D\x45\xF5\x50\x8D\x45\xF1\x50\x51",
                "xxxxxxx????xxxxxxxxxxxxxxxxxxxxxx???xxxx????xxxxxxxxxxxx");
            Globals::SendFlyTargetingPacket = B_SendFlyTargetingPacket;
            if (DbgSession)
                cout << B_SendFlyTargetingPacket << endl;
            LOG("SendFlyTargetingPacket: " << B_SendFlyTargetingPacket);

            /* DWORD B_RecvWhisper = FindSignature(xorstr_("PolandMT2.exe"),
                 "\x55\x8B\xEC\x83\xE4\xF8\x83\xEC\x24\xA1\x40\x00\x00\x00\x00\x02\x33\xC4\x89\x44\x24\x20\x8B",
                 "xxxx??xx?????xxxxxxxx");
             Globals::RecvWhisper = B_RecvWhisper;
             if (DbgSession)
                 cout << "RecvWhisper: " << B_RecvWhisper << endl;*/

            DWORD B_SendItemUse = FindSignature(xorstr_("PolandMT2.exe"),
                "\x55\x8B\xEC\x51\x51\x56\x8B\xF1\xE8\x74\xE6\xFF\xFF\x84\xC0\x74\x4F\x66\x8B\x45\x08\x51\x8B\xD4\x66\x89\x02\x8A\x45\x0A\x88\x42\x02\xE8\x7C\x02\x00\x00",
                "xxxxxxxxx????xxxxxxxxxxxxxxxxxxxxx????");
            Globals::SendItemUse = B_SendItemUse;
            if (DbgSession)
                cout << "SendItemUse: " << B_SendItemUse << endl;
            LOG("SendItemUse: " << B_SendItemUse);

            DWORD B_Lowienie = FindSignature(xorstr_("PolandMT2.exe"),
                "\x55\x8B\xEC\x83\xEC\x10\x53\x33\xDB\xC6\x45",
                "xxxxxxxxxxx");
            Globals::Lowienie = B_Lowienie;
            if (DbgSession)
                cout << "Lowienie: " << B_Lowienie << endl;
            LOG("Lowienie: " << B_Lowienie);
            //55 8B EC 83 EC 10 53 33 DB C6 45
            /*
            DWORD B_attackEntity = FindSignature(xorstr_("PolandMT2.exe"),
                "\x55\x8B\xEC\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x81\xEC\x00\x00\x00\x00\xA1\x00\x00\x00\x00\x33\xC5\x89\x45\xF0\x53\x56\x57\x50\x8D\x45\xF4\x64\xA3\x00\x00\x00\x00\x8B\xF9\x8D\x85\x00\x00\x00\x00",
                "xxxxxx????xx????xxx????x????xxxxxxxxxxxxxx????xxxx????");
            Globals::attackEntity = B_attackEntity;
            if (DbgSession)
                cout << "recvWhisperPacketFunction: " << B_attackEntity << endl;
           // inline const char* recvWhisperPacketFunctionPattern = "\x55\x8B\xEC\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x81\xEC\x00\x00\x00\x00\xA1\x00\x00\x00\x00\x33\xC5\x89\x45\xF0\x53\x56\x57\x50\x8D\x45\xF4\x64\xA3\x00\x00\x00\x00\x8B\xF9\x8D\x85\x00\x00\x00\x00";
           //inline const char* recvWhisperPacketFunctionMask = "xxxxxx????xx????xxx????x????xxxxxxxxxxxxxx????xxxx????";
    */
            DWORD B_RecvStunPacket = FindSignature(xorstr_("PolandMT2.exe"),
                "\x55\x8B\xEC\x51\x51\x8D\x45\xF8\x50\x6A\x05\xE8\xF4\x7D\x1F\x00\x84\xC0\x75\x0E\xB9\xD8\x42\xAE\x02\xE8\xC2\x5D\x1E\x00\x32\xC0\xC9\xC3",
                "xxxxxxxxxxxx????xxxxx????x????xxxx");
            Globals::RecvStunPacket = B_RecvStunPacket;
            if (DbgSession)
                cout << "RecvStunPacket: " << B_RecvStunPacket << endl;
            LOG("RecvStunPacket: " << B_RecvStunPacket);
            // RecvStunPacket

            DWORD B_SendGuildOfferPacket = FindSignature(xorstr_("PolandMT2.exe"),
                "\x55\x8B\xEC\x51\x56\x8D\x45\xFC\x66\xC7\x45\xFC\x50\x04\x50\x6A\x02\x8B\xF1\xE8\x70\x54\x1F\x00\x84\xC0\x74\x29\x8D\x45\x08\x8B\xCE\x50\x6A\x04\xE8\x5F\x54\x1F\x00\x84\xC0\x74\x18\xFF\x75\x08\x68\xB0\x4E\xAE\x02\xE8\xFF\x34\x1E\x00\x59\x59\x8B\xCE\xE8\x59\x54\x1F\x00\xEB\x02\x32\xC0\x5E\xC9\xC2\x04\x00",
                "xxxxxxxxxxxxxxxxxxxx????xxxxxxxxxxxxx????xxxxxxxx????x????xxxxx????xxxxxxxxx");
            Globals::SendGuildOfferPacket = B_SendGuildOfferPacket;
            if (DbgSession)
                cout << "SendGuildOfferPacket: " << B_SendGuildOfferPacket << endl;
            LOG("SendGuildOfferPacket: " << B_SendGuildOfferPacket);
            //SendGuildOfferPacket

            DWORD B_SendPointResetPacket = FindSignature(xorstr_("PolandMT2.exe"),
                "\x56\x68\xE8\xAF\xA1\x02\x8B\xF1\xE8\x81\xDE\x06\x00\x8B\x8E\x00\x02\x00\x00\xBA\xA4\x47\xAE\x02\x50\xE8\xDF\x4E\x31\x00\x59\x59\xB0\x01\x5E\xC3",
                "xx????xxx????xxxxxxx????xx????xxxxxx");
            Globals::SendPointResetPacket = B_SendPointResetPacket;
            if (DbgSession)
                cout << "SendPointResetPacket: " << B_SendPointResetPacket << endl;
            LOG("SendPointResetPacket: " << B_SendPointResetPacket);

            DWORD B_RecvChatPacket = FindSignature(xorstr_("PolandMT2.exe"),
                "\x6A\x3C\xB8\xBF\xC7\x7F\x02\xE8\x67\x89\x41\x00\x8B\xF1\x8D\x45\x08\xC7\x45\xFC\x01\x00\x00\x00\x50\xE8\x49\xEE\x00\x00\x8B\x5D\x30\x8D\x7D\xD8\x33\xC0\xAB\xAB\xAB\xAB\x83\x65\xE8\x00\xC7\x45\xEC\x0F\x00\x00\x00\xC6\x45\xD8\x00\xC6\x45\xFC\x02\xEB\x5B",
                "xxx????x????xxxxxxxxxxxxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
            Globals::RecvChatPacket = B_RecvChatPacket;
            if (DbgSession)
                cout << "RecvChatPacket: " << B_RecvChatPacket << endl;
            LOG("RecvChatPacket: " << B_RecvChatPacket);

            DWORD B_RecvWhisperPacket = FindSignature(xorstr_("PolandMT2.exe"),
                "\x55\x8B\xEC\x81\xEC\x3C\x02\x00\x00\xA1\x00\x34\xB9\x02\x33\xC5\x89\x45\xFC\x53\x56\x57\x8D\x85\xC8\xFD\xFF\xFF\x8B\xF9\x50\x6A\x25\xE8\x5A\x81\x1F\x00\x84\xC0\x75\x0F\x8B\x4D\xFC\x5F\x5E\x33\xCD\x5B\xE8\xD6\x60\x41\x00\xC9\xC3",
                "xxxxx????x????xxxxxxxxxx????xxxxxx????xxxxxxxxxxxxx????xx");
            Globals::RecvWhisperPacket = B_RecvWhisperPacket;
            if (DbgSession)
                cout << "RecvWhisperPacket: " << B_RecvWhisperPacket << endl;
            LOG("RecvWhisperPacket: " << B_RecvWhisperPacket);

            DWORD B_SendItemPickUpPacket = FindSignature(xorstr_("PolandMT2.exe"),
                "\x55\x8B\xEC\x51\x51\x56\x8B\xF1\xE8\x4C\xE1\xFF\xFF\x84\xC0\x75\x04\xFE\xC0\xEB\x30\x8B\x45\x08\x8B\xCE\x89\x45\xF9\x8D\x45\xF8\x50\x6A\x05\xC6\x45\xF8\x0F\xE8\x82\x39\x1E\x00\x84\xC0\x75\x0E\xB9\x84\x64\xAE\x02\xE8\x27\x19\x1D\x00\x32\xC0\xEB\x07",
                "xxxxxxxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxxx????x????xxxx");
            Globals::SendItemPickUpPacket = B_SendItemPickUpPacket;
            if (DbgSession)
                cout << "SendItemPickUpPacket: " << B_SendItemPickUpPacket << endl;
            LOG("SendItemPickUpPacket: " << B_SendItemPickUpPacket);

            DWORD B_NEW_GetPixelPosition = FindSignature(xorstr_("PolandMT2.exe"),
                "\x55\x8B\xEC\x81\xC1\x20\x02\x00\x00\xE8\x95\xBF\x33\x00\x8B\x55\x08\x8B\xC8\xE8\xD6\x1A\x34\x00\x5D\xC2\x04\x00",
                "xxxxx????x????xxxxxx????xxxx");
            Globals::NEW_GetPixelPosition = B_NEW_GetPixelPosition;
            if (DbgSession)
                cout << "NEW_GetPixelPosition: " << B_NEW_GetPixelPosition << endl;
            LOG("NEW_GetPixelPosition: " << B_NEW_GetPixelPosition);

            break;
        }
        case Ervelia:
        {
            //char P_PlayerBase[] = "\x55\x8B\xEC\x8B\x0D\x00\x00\x00\x00\x8D\x49\x04\x8B\x01\x5D";
            //char M_PlayerBase[] = "xxxxx????xxxxxx";
            //DWORD B_PlayerBase = FindSignature(xorstr_("metin2client.exe"), P_PlayerBase, M_PlayerBase);
            //Globals::PlayerBase = *(DWORD*)(B_PlayerBase + 0x5);
            Globals::iCPythonCharacterManagerInstance = 0x52DA874;
            cout << "CPythonCharacterManagerInstance: " << std::hex << Globals::iCPythonCharacterManagerInstance << std::endl;

            //char P_PlayerGetTargetVID[] = {"\x55\x8B\xEC\x51\x89\x4D\xFC\x8B\x45\xFC\x8B\x80\x00\x00\x00\x00\x8B\xE5\x5D\xC3"};//  \x81\x30\xFB\x04\x00\x5D
            //char M_PlayerGetTargetVID[] = "xxxxxxxxxxxx????xxxx";
            B_PlayerGetTargetVID = FindSignature(xorstr_("metin2client.exe"),
                "\x55\x8B\xEC\x51\x89\x4D\xFC\x8B\x45\xFC\x8B\x80\x00\x00\x00\x00\x8B\xE5\x5D\xC3",
                "xxxxxxxxxxxx????xxxx");
            Globals::PlayerGetTargetVID = B_PlayerGetTargetVID; //<-address
            cout << "PlayerGetTargetVID: " << std::hex << Globals::PlayerGetTargetVID << std::endl;
            break;
        }
        default:
        {
            cout << "Nothin found." << endl;
            break;
        }
        if (g_LogFile.is_open())
        {
            g_LogFile.close();
        }
        }
    }

