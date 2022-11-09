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

	TileTool,

	GailRoom,

	Store,

	Stage01,

	Forest,

	BossMap,

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
//##				타일					##
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

	Size
};

enum class MonsterBehavior
{
	Idle,
	Walk,

	Size
};