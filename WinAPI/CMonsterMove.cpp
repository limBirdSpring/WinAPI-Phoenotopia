#include "framework.h"
#include "CMonsterMove.h"
#include "CMonster.h"

CMonsterMove::~CMonsterMove()
{
}

void CMonsterMove::Init()
{
	coolTime = -1;
	srand(time(NULL));
}

void CMonsterMove::Update()
{
	
	if (coolTime > 0)
	{
		coolTime -= DT;
	}

	if (coolTime == 0)
	{
		coolTime = -1;
		pMonster->SetBehavior(MonsterBehavior::Idle);
	}

	int random = rand() % 3 - 1;

	Vector monPos = pMonster->GetPos();

	pMonster->SetDir(Vector(random, 0));

	monPos.x += pMonster->GetDir().x * DT * pMonster->GetSpeed();
	pMonster->SetPos(monPos.x, monPos.y);

}

void CMonsterMove::Release()
{
}
