#include "pch.h"
#pragma once
using namespace std;
namespace GameFunctions
{
	namespace t
	{
		typedef bool(__thiscall* t_SendUseItem)(void* StreamInstance, WORD itemID);
		typedef bool(__thiscall* t_GetTargetVID)(void* StreamInstance, DWORD a2);
		typedef bool(__thiscall* t_SendAttackPacket)(void* StreamInstance, char a2, DWORD a3);
		typedef void(__thiscall* t_AppendChat)(void* This, int iType, const char* c_szChat, int a4, int a5);
		typedef char(__thiscall* t_SendChatPacket)(void* StreamInstance, const char* c_szChat, uint8_t byType);//CPythonNetworkStream::SendChatPacket
		typedef char(__thiscall* t_SendUseSkillPacket)(void* StreamInstance, uint32_t dwSkillIndex, uint32_t dwTargetVID);//CPythonNetworkStream::SendUseSkillPacket
		typedef int(__thiscall* t_SendShootPacket)(void* StreamInstance, uint32_t skill);//CPythonNetworkStream::SendShootPacket
		typedef int(__thiscall* t_SendFlyTargetingPacket)(void* StreamInstance, uint32_t dwTargetVID, int kPPosTarget);//CPythonNetworkStream::SendFlyTargetingPacket
		typedef int(__thiscall* t_SendAddFlyTargetingPacket)(void* StreamInstance, uint32_t dwTargetVID, int kPPosTarget);//CPythonNetworkStream::SendAddFlyTargetingPacket
		typedef int(__thiscall* t_RecvStunPacket)(void* StreamInstance);
		typedef int(__thiscall* t_SendGuildOfferPacket)(void* StreamInstance, int exp);//CPythonNetworkStream::SendGuildOfferPacket(void *this, int exp)
		typedef int(__thiscall* t_SendPointResetPacket)(void* StreamInstance);//CPythonNetworkStream::SendPointResetPacket(void* StreamInstance)
		typedef int(__thiscall* t_NEW_GetPixelPosition)(void* StreamInstance, sdk::util::metin_structs::Point2D& pPixelPosition);
		typedef int(__thiscall* t_GetMainInstancePtr)(void* StreamInstance);		//CPythonNetworkStream::GetMainInstancePtr
		typedef int(__thiscall* t_RecvChatPacket)(char a1, int a2, int a3, int a4, int a5, int a6, char a7, int a8, int a9, int a10, int a11);//CPythonNetworkStream::RecvChatPacket(const TPacketGCChat& kChat)
		typedef void(__thiscall* t_RecvWhisperPacket)(DWORD*, int a2, int a3, int a4);
		typedef int(__thiscall* t_SendItemPickUpPacket)(void* StreamInstance, WORD itemID);
	}
	class c_funcs : public s<c_funcs>
	{
	public:
		t::t_SendUseItem				f_SendUseItem = 0;				//CPythonNetworkStream
		t::t_GetTargetVID				f_GetTargetVID = 0;				//CPythonNetworkStream
		t::t_SendAttackPacket			f_SendAttackPacket = 0;			//CPythonNetworkStream
		t::t_AppendChat					f_AppendChat = 0;				//CPythonNetworkStream
		t::t_SendChatPacket				f_SendChatPacket = 0;			//CPythonNetworkStream
		t::t_SendUseSkillPacket			f_SendUseSkillPacket = 0;		//CPythonNetworkStream
		t::t_SendShootPacket			f_SendShootPacket = 0;			//CPythonNetworkStream
		t::t_SendFlyTargetingPacket		f_SendFlyTargetingPacket = 0;	//CPythonNetworkStream
		t::t_RecvStunPacket				f_RecvStunPacket = 0;			//CPythonNetworkStream
		t::t_SendGuildOfferPacket		f_SendGuildOfferPacket = 0;		//CPythonNetworkStream
		t::t_SendPointResetPacket		f_SendPointResetPacket = 0;		//CPythonNetworkStream
		t::t_NEW_GetPixelPosition		f_NEW_GetPixelPosition = 0;		//CPythonNetworkStream
		t::t_GetMainInstancePtr			f_GetMainInstancePtr = 0;		//CPythonNetworkStream
		t::t_RecvChatPacket				f_RecvChatPacket = 0;			//CPythonNetworkStream
		t::t_RecvWhisperPacket			f_RecvWhisperPacket = 0;		//CPythonNetworkStream
		t::t_SendItemPickUpPacket		f_SendItemPickUpPacket = 0;		//CPythonNetworkStream
		//t::t_IsAttacking				f_IsAttacking = 0;					//CPythonPlayer
		//t::t_OnHit						f_OnHit = 0;					//CPythonPlayerEventHandler
		//t::t_SendItemPickUpPacket		f_SendItemPickUpPacket = 0;			//CPythonNetworkStream
		//t::t_EterPackGet				f_EterPackGet = 0;					//CEterPackManager
		//t::t_CPythonApplicationProcess	f_CPythonApplicationProcess = 0;
		uint32_t						o_SendSelectCharacter = 0;
		uint32_t						o_SendCharacterStatePacket = 0;
		uint32_t						o_IsAttacking = 0;
		uint32_t						o_SendHitEvent = 0;						//for servers that use lalaker patch, inline dmg
		uint32_t						o_SendShootPacket = 0;
		uint32_t						o_CPythonApplicationProcess = 0;
		uint32_t*						NetPointer = NULL;
	};

	static void SetAddies();
	static void HookToGetNetPointer();
	static void HookedGetMainInstancePtr(uint32_t* StreamInstance);
	static void UseSkill(int SkillIndex);
	
};

typedef int(*tHook)(const char*);
tHook oHook;
typedef std::map<DWORD, DWORD*>	TCharacterInstanceMap;

void GameFunctions::HookedGetMainInstancePtr(uint32_t* StreamInstance) {
	cout << "Hooked" << endl;
	GameFunctions::c_funcs::Instance().NetPointer = StreamInstance;
}

void GameFunctions::HookToGetNetPointer() {
	if (Globals::GetMainInstancePtr && GameFunctions::c_funcs::Instance().f_GetMainInstancePtr) {
		cout << "11" << endl;
		GameFunctions::c_funcs::Instance().f_GetMainInstancePtr = (GameFunctions::t::t_GetMainInstancePtr)DetourFunction((PBYTE)GameFunctions::c_funcs::Instance().f_GetMainInstancePtr, (PBYTE)HookedGetMainInstancePtr);
	}

}

void GameFunctions::SetAddies() {
	if (Globals::SendItemUse) {
		GameFunctions::c_funcs::Instance().f_SendUseItem = decltype(GameFunctions::c_funcs::Instance().f_SendUseItem)(Globals::SendItemUse);
	}
	if (Globals::SendUseSkillPacket) {
		GameFunctions::c_funcs::Instance().f_SendUseSkillPacket = decltype(GameFunctions::c_funcs::Instance().f_SendUseSkillPacket)(Globals::SendUseSkillPacket);
	}
	if (Globals::GetMainInstancePtr) {
		GameFunctions::c_funcs::Instance().f_GetMainInstancePtr = decltype(GameFunctions::c_funcs::Instance().f_GetMainInstancePtr)(Globals::GetMainInstancePtr);
		cout << "222" << endl;
	}

}

void GameFunctions::UseSkill(int SkillIndex) {
	if (GameFunctions::c_funcs::Instance().NetPointer && GameFunctions::c_funcs::Instance().f_SendUseSkillPacket) {

		auto NetPointer = GameFunctions::c_funcs::Instance().NetPointer;
		GameFunctions::c_funcs::Instance().f_SendUseSkillPacket(NetPointer, SkillIndex, 0);
		
	}
}

