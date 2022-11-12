#include "framework.h"
#include "CMonsterJump.h"
#include "CMonster.h"

CMonsterJump::~CMonsterJump()
{
}

void CMonsterJump::Init()
{
}

void CMonsterJump::Update()
{

	Vector monPos = pMonster->GetPos();

	if (pMonster->GetGround() != 0)
	{
		int random = rand() % 3 - 1;
		pMonster->SetDir(Vector(random, 0));
		pMonster->SetPos(monPos.x, --monPos.y);
		pMonster->SetGravity(-200);
	}
	//몬스터 해당방향으로 점프이동
	monPos.x += pMonster->GetDir().x * DT * pMonster->GetSpeed();
	pMonster->SetPos(monPos.x, monPos.y);
	

	//pMonster->SetBehavior(MonsterBehavior::Follow);
}

void CMonsterJump::Release()
{
}
