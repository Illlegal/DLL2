//#include "pch.h"
#pragma once
using namespace std;
class GameFunctionsCustom
{
	public:
		static DWORD Baseoffset;
		static DWORD PlayerX;
		static DWORD PlayerY;
		static DWORD XOffset;
		static DWORD YOffset;
		static DWORD ZOffset;
		static DWORD MobName;
		static DWORD MobType;
		static DWORD MobVID;
		static DWORD Alive;
	
		int InstanceBaseGetDistance(DWORD dVID);
};

DWORD GameFunctionsCustom::Baseoffset = 0xC;
DWORD GameFunctionsCustom::PlayerX = 0x1AC;
DWORD GameFunctionsCustom::PlayerY = 0x1B0;
DWORD GameFunctionsCustom::XOffset = 0x748; //OR 570
DWORD GameFunctionsCustom::YOffset = 0x74C; //OR 574
DWORD GameFunctionsCustom::ZOffset = 0x750; //OR 578
DWORD GameFunctionsCustom::MobName = 0x10;
DWORD GameFunctionsCustom::MobType = 0x62C;
DWORD GameFunctionsCustom::MobVID = 0x798;
DWORD GameFunctionsCustom::Alive = 0x738;


int GameFunctionsCustom::InstanceBaseGetDistance(DWORD dVID) {
	DWORD dOffset = NULL;
	DWORD Instance = 0x4;
	
	for (int i = 0; i < 300; i++)
	{
		if (*(int*)(*(DWORD*)(*(DWORD*)Globals::MobBase + Instance) + GameFunctionsCustom::MobVID) == dVID)
		{
			dOffset = Instance;
			break;
		}
	}
	if (dOffset != NULL) {
		float Mob_X = *(BYTE*)(*(DWORD*)(*(DWORD*)Globals::MobBase + dOffset) + GameFunctionsCustom::XOffset); //X value for mob with actual offset
		float Mob_Y = *(BYTE*)(*(DWORD*)(*(DWORD*)Globals::MobBase + dOffset) + GameFunctionsCustom::YOffset); //Y value for mob with actual offset
		float PC_X = *(BYTE*)(*(DWORD*)(*(DWORD*)Globals::PlayerBase + GameFunctionsCustom::Baseoffset) + GameFunctionsCustom::PlayerX);//X value for PLAYER
		float PC_Y = *(BYTE*)(*(DWORD*)(*(DWORD*)Globals::PlayerBase + GameFunctionsCustom::Baseoffset) + GameFunctionsCustom::PlayerY);//X value for PLAYER
		return sqrt(pow((Mob_X - PC_X), 2) + pow((Mob_Y - PC_Y), 2));
	}
	
	return 1000;
}