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
	int random = rand() % 2;

	Vector monPos = pMonster->GetPos();

	if (pMonster->GetGround() != 0)
	{
		if (coolTime > 0)
		{
			coolTime = 0;
			pMonster->SetBehavior(MonsterBehavior::Idle);
			return;
		}

		else if (GAME->GetPlayerPos().x > pMonster->GetPos().x)
		{
			pMonster->SetDir(Vector(1, 0));
		}
		else
		{
			pMonster->SetDir(Vector(-1, 0));
		}
		pMonster->SetPos(monPos.x, --monPos.y);
	
		if (random==0) pMonster->SetGravity(-100);
		else pMonster->SetGravity(-230);

		pMonster->SetGround(0);
		pMonster->SetPlatform(0);
		
	}
	//몬스터 해당방향으로 점프이동
	monPos.x += pMonster->GetDir().x * DT * pMonster->GetSpeed();
	pMonster->SetPos(monPos.x, monPos.y);
	
	coolTime += DT;
	//pMonster->SetBehavior(MonsterBehavior::Follow);
}

void CMonsterJump::Release()
{
}
