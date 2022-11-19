#pragma once

#include "resource.h"

//========================================
//##    전역변수(인스턴스, 윈도우 핸들)	##
//========================================

extern HINSTANCE hInst;
extern HWND hWnd;

//========================================
//##			윈도우 설정				##
//========================================

#define WINSTARTX   100
#define WINSTARTY   100
#define WINSIZEX	1280
#define	WINSIZEY	720
#define WINSTYLE	WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX

//========================================
//##			게임씬 그룹				##
//========================================

enum class GroupScene
{
	Title,

	Load,

	TileTool,

	GailRoom,

	Store,

	Gym,

	Stage01,

	Forest,

	BossMap,

	Field,

	PrinceForest,

	Inventory,

	SetUp,

	Ending,

	Dead,

	Size,
};

//========================================
//##				레이어				##
//========================================

enum class Layer
{
	Default,
	BackGround,
	MiddleGround,
	Cloud,
	Tile,
	Door,
	NPC,
	Things,
	Monster,
	Boss,
	FlyingMonster,
	MonsterAttack,
	Player,
	Missile,
	FrontGround,
	TalkBox,
	Ui,
	Size,
};

//========================================
//##				타일					##
//========================================

enum class TypeTile
{
	None,
	Ground,
	Platform,
	Wall,
	Stair,
	Size,
};

//========================================
//##				모션 				##
//========================================

enum class Behavior
{
	Idle,
	Walk,
	Run,
	Jump,
	DownJump,
	Fall,
	Down,
	AttackReady,
	Attack,
	Attack2,
	CriticalReady,
	Critical,
	Damage,
	Talk,
	Wonder,
	Bored,
	Move,
	Bat,
	Push,
	Dead,

	Size
};

enum class MonsterBehavior
{
	Idle,
	Move,
	Run,
	Follow,
	Jump,
	Damage,
	Attack,
	Fly,

	Size
};

enum class BossBehavior
{
	Appear,
	Idle,
	Move,
	Attack,
	Attack2,
	Dead,

	Size
};


//========================================
//##				기타 				##
//========================================

enum class MainQuest
{
	Start,

	VisitStore,
	FindBoard,
	LearnAttack,
	SavePrince,

	Size
};

enum class ItemType
{
	Food,
	Weapon,
	Quest,

	Size
};