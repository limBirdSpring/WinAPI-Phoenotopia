#include "framework.h"
#include "CMonsterFollow.h"
#include "CMonster.h"



CMonsterFollow::~CMonsterFollow()
{
}

void CMonsterFollow::Init()
{
}

void CMonsterFollow::Update()
{
	Vector monPos = pMonster->GetPos();

	if (GAME->GetPlayerPos().x > pMonster->GetPos().x)
	{
		pMonster->SetDir(Vector(1,0));
	}
	else
	{
		pMonster->SetDir(Vector(-1, 0));
	}
	monPos.x += pMonster->GetDir().x * DT * pMonster->GetSpeed();
	pMonster->SetPos(monPos.x, monPos.y);
}

void CMonsterFollow::Release()
{
}
