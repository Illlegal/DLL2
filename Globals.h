#include "pch.h"
#pragma once
using namespace std;
namespace Globals
{

	//######################################################################################################################################
	//static ServerName Server;
	static bool UsePythonFunctions;
	//static map<DWORD, TCItemData*> itemProtoList;
	//static map<DWORD, const char*> itemProtoNames;
	//static map<DWORD, TGroundItemInstance*> groundItemList;

	//static DWORD hEntryBaseAddress;
	//static DWORD hEntryBaseSize;
	//static HMODULE hModule;
	//static HWND mainHwnd;


	//###############################   PLAYER
	static DWORD PlayerBase;
	static DWORD PlayerBaseOffset;
	static DWORD PlayerGetTargetVID;
	static DWORD pCPythonCharacterManagerInstance;
	static DWORD iCPythonCharacterManagerInstance;
	
	//###############################	MOB
	static DWORD MobBase;

	//###############################	NETWORK
	static DWORD SendAttackPacket;
	static DWORD AppendChat;
	static DWORD SendChatPacket;
	static DWORD SendUseSkillPacket;
	static DWORD GetMainInstancePtr;
	static DWORD SendShootPacket;
	static DWORD SendAddFlyTargetingPacket;
	static DWORD SendFlyTargetingPacket;
	static DWORD RecvStunPacket;
	static DWORD SendGuildOfferPacket;
	static DWORD SendPointResetPacket;
	static DWORD RecvChatPacket;
	static DWORD RecvWhisperPacket;
	static DWORD SendItemPickUpPacket;
	//############################## CInstanceBase
	static DWORD NEW_GetPixelPosition;

	static DWORD RecvWhisper;
	static DWORD SendItemUse;
	static DWORD Lowienie;
	
	//############################### MOJE
	static DWORD attackEntity;
	//###############################	CharacterManager
	static DWORD pCInstanceBaseAvoidObject;
	static DWORD pCInstanceBaseBlockMovement;
	static DWORD pCInstanceBaseGetInstanceType;
	static DWORD pCInstanceBaseGetInstanceVirtualNumber;
	static DWORD pCInstanceBaseGetNameString;
	static DWORD pCInstanceBaseGetRotation;
	static DWORD pCInstanceBaseIsDead;
	static DWORD pCInstanceBaseIsMountingHorse;
	static DWORD pCInstanceBaseNEW_GetPixelPosition;
	static DWORD pCInstanceBaseNEW_LookAtDestPixelPosition;
	static DWORD pCInstanceBaseNEW_MoveToDestPixelPositionDirection;
	static DWORD pCInstanceBaseSCRIPT_SetPixelPosition;
	static DWORD pCInstanceBase__SetAffect;
	static DWORD pCItemDataGetName;
	static DWORD pCItemManagerGetItemDataPointer;
	//static void ReDeclarationLocals();
	typedef bool(__thiscall* tCInstanceBaseIsDead)(void* This);
	static tCInstanceBaseIsDead CInstanceBaseIsDead;
};



/*

	enum EType
	{
		TYPE_ENEMY,
		TYPE_NPC,
		TYPE_STONE,
		TYPE_WARP,
		TYPE_DOOR,
		TYPE_BUILDING,
		TYPE_PC,
		TYPE_POLY,
		TYPE_HORSE,
		TYPE_GOTO,
		TYPE_SHOP,
		TYPE_PET,
		TYPE_MOUNT,
		TYPE_GROWTH_PET,
		TYPE_BUFFBOT,
		TYPE_ATTACK_PET,

		TYPE_OBJECT,
		// Only For Client
	};

	//###############################   PLAYER Struct
	struct sPlayer {
		string Name;	//Player Name
		int Level;		//Player Level
		float MovSpeed;	//Movement Speed
		float AttSpeed;	//Attack Speed
		int WeaponID;	//ID of equped weapon
		int AttackType;	//Animation of Attack, eq 0-4
		float x;
		float y;		//Cords of player
		float z;
	}static  Player;

*/