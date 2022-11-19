#pragma once

#include "resource.h"

//========================================
//##    ��������(�ν��Ͻ�, ������ �ڵ�)	##
//========================================

extern HINSTANCE hInst;
extern HWND hWnd;

//========================================
//##			������ ����				##
//========================================

#define WINSTARTX   100
#define WINSTARTY   100
#define WINSIZEX	1280
#define	WINSIZEY	720
#define WINSTYLE	WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX

//========================================
//##			���Ӿ� �׷�				##
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
//##				���̾�				##
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
//##				Ÿ��					##
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
//##				��� 				##
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
//##				��Ÿ 				##
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