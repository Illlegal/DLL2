#include <math.h>
namespace sdk
{
	namespace util
	{
		namespace metin_structs
		{
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

				TYPE_OBJECT, // Only For Client
			};
			enum
			{
				FUNC_WAIT,
				FUNC_MOVE,
				FUNC_ATTACK,
				FUNC_COMBO,
				FUNC_MOB_SKILL,
				FUNC_EMOTION,
				FUNC_SKILL = 0x80,
			};
			enum MapFlags
			{
				ATTRIBUTE_BLOCK = (1 << 0),
				ATTRIBUTE_WATER = (1 << 1),
				ATTRIBUTE_BANPK = (1 << 2),
			};
			class Point2D
			{
			public:
				Point2D(float x = 0.f, float y = 0.f) { this->x = x; this->y = y; }

				inline float distance(Point2D* p) { return sqrt((p->x - x) * (p->x - x) + (p->y - y) * (p->y - y)); }
				float angle(Point2D* p);
				inline void absoluteY() { y = abs(y); }

				inline int getIntX() { return (int)x; }
				inline int getIntY() { return (int)y; }

				inline void setIntX(int x) { this->x = (float)x; }
				inline void setIntY(int y) { this->y = (float)y; }

				bool operator==(Point2D& a) { return getIntX() == a.getIntX() && getIntY() == a.getIntY(); }

				float x;
				float y;
			};
		}
	}
}
typedef struct command_attack
{
	BYTE	header;
	BYTE	bType;			// °ø°Ý À¯Çü
	DWORD	dwVictimVID;	// Àû VID
	BYTE	bCRCMagicCubeProcPiece;
	BYTE	bCRCMagicCubeFilePiece;
} TPacketCGAttack;
typedef struct command_move_aeldra
{
	WORD	header;
	DWORD	size;
	BYTE	unknown;
	LONG		lX;
	LONG		lY;
	WORD		bFunc;
	WORD		bArg;
	BYTE		bRot;
	DWORD	dwTime;
} TPacketCGStatePacket;

typedef struct command_sync_position
{
	BYTE        header;
	WORD		wSize;
} TPacketCGSyncPosition;

typedef struct command_sync_position_element
{
	DWORD       dwVID;
	long        lX;
	long        lY;
} TPacketCGSyncPositionElement;

typedef struct packet_fly
{
	BYTE        bHeader;
	BYTE        bType;
	DWORD       dwStartVID;
	DWORD       dwEndVID;
} TPacketGCCreateFly;
typedef struct packet_add_char
{
	BYTE        header;

	DWORD       dwVID;

} TPacketGCCharacterAdd;

typedef struct packet_update_char
{
	BYTE        header;
	DWORD       dwVID;
} TPacketGCCharacterUpdate;

typedef struct packet_sfishing
{
	BYTE header;
} TPacketCGFishingX;

typedef struct packet_fishing
{
	BYTE header;
	BYTE subheader;
	DWORD info;
	BYTE dir;
} TPacketGCFishing;

typedef struct packet_ground_del_item
{
	BYTE		header;
	DWORD		vid;
} TPacketGCItemGroundDel;

typedef struct packet_ground_add_item
{
	BYTE        bHeader;
	long        lX;
	long		lY;
	long		lZ;

	DWORD       dwVID;
	DWORD       dwVnum;
} TPacketGCItemGroundAdd;
/*
typedef struct packet_item_ownership
{
	BYTE        bHeader;
	DWORD       dwVID;
	char        szName[CHARACTER_NAME_MAX_LEN + 1];
} TPacketGCItemOwnership;

typedef struct packet_del_char
{
	BYTE	header;
	DWORD	dwVID;
} TPacketGCCharacterDelete;

typedef struct packet_whisper   // °¡º¯ ÆÐÅ¶    
{
	BYTE        bHeader;
	WORD        wSize;
	BYTE        bType;
	char        szNameFrom[CHARACTER_NAME_MAX_LEN + 1];
} TPacketGCWhisper;

typedef struct SMobSkillLevel
{
	DWORD       dwVnum;
	BYTE        bLevel;
} TMobSkillLevel;

typedef struct SMobTable_r255
{
	DWORD       dwVnum;
	char        szName[CHARACTER_NAME_MAX_LEN + 1];
	char        szLocaleName[CHARACTER_NAME_MAX_LEN + 1];

	BYTE        bType;                  // Monster, NPC
	BYTE        bRank;                  // PAWN, KNIGHT, KING
	//BYTE        bBattleType;            // MELEE, etc..
	//BYTE        bLevel;                 // Level
	//BYTE        bSize;

	//DWORD       dwGoldMin;
	//DWORD       dwGoldMax;
	//DWORD       dwExp;
	//DWORD       dwMaxHP;
	//BYTE        bRegenCycle;
	//BYTE        bRegenPercent;
	//WORD        wDef;

	//DWORD       dwAIFlag;
	//DWORD       dwRaceFlag;
	//DWORD       dwImmuneFlag;

	//BYTE        bStr, bDex, bCon, bInt;
	//DWORD       dwDamageRange[2];

	//short       sAttackSpeed;
	//short       sMovingSpeed;
	//BYTE        bAggresiveHPPct;
	//WORD        wAggressiveSight;
	//WORD        wAttackRange;

	//char        cEnchants[6];
	//char        cResists[6];

	//DWORD       dwResurrectionVnum;
	//DWORD       dwDropItemVnum;

	//BYTE        bMountCapacity;
	//BYTE        bOnClickType;

	//BYTE        bEmpire;
	//char        szFolder[64 + 1];
	//float       fDamMultiply;
	//DWORD       dwSummonVnum;
	//DWORD       dwDrainSP;
	//DWORD		dwMonsterColor;
	//DWORD       dwPolymorphItemVnum;

	//TMobSkillLevel	Skills[5];

	//BYTE		bBerserkPoint;
	//BYTE		bStoneSkinPoint;
	//BYTE		bGodSpeedPoint;
	//BYTE		bDeathBlowPoint;
	//BYTE		bRevivePoint;
} TMobTable_r255;
typedef TMobTable_r255 SMobTable, TMobTable;

typedef struct SGroundItemInstance
{
	DWORD					Instance;
	DWORD					dwVirtualNumber;
	D3DXVECTOR3				v3EndPosition;
	D3DXVECTOR3				v3RotationAxis;
	D3DXQUATERNION			qEnd;
	D3DXVECTOR3				v3Center;
	DWORD* ThingInstance;
	DWORD					dwStartTime;
	DWORD					dwEndTime;
	DWORD					eDropSoundType;
	std::string				stOwnership;
} TGroundItemInstance;

typedef struct SGroundItemInstanceGlobal
{
	DWORD					Instance;
	DWORD					dwVirtualNumber;
	D3DXVECTOR3				v3EndPosition;
	D3DXVECTOR3				v3RotationAxis;
	D3DXQUATERNION			qEnd;
	D3DXVECTOR3				v3Center;
	DWORD* ThingInstance;
	DWORD					dwStartTime;
	DWORD					dwEndTime;
	DWORD					eDropSoundType;
	BYTE					unk2[756];
	char  stOwnership[24];
} TGroundItemInstanceGlobal;

//typedef MapaGlobal::std::map<DWORD, TGroundItemInstanceGlobal*> TGroundItemInstanceMapGlobal;
//typedef std::map<DWORD, TGroundItemInstance*> TGroundItemInstanceMap;
*/