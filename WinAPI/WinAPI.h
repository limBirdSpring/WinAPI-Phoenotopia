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

	TileTool,

	GailRoom,

	Store,

	Gym,

	Stage01,

	Forest,

	BossMap,

	Inventory,

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
	Tile,
	Things,
	NPC,
	Player,
	Missile,
	Monster,

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

	Size
};

enum class MonsterBehavior
{
	Idle,
	Walk,

	Size
};