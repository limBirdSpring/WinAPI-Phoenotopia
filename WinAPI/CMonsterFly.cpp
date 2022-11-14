#include "framework.h"
#include "CMonsterFly.h"
#include "CMonster.h"

CMonsterFly::~CMonsterFly()
{
}

void CMonsterFly::Init()
{
}

void CMonsterFly::Update()
{
	if (coolTime == 0)
	{
		playerPos = GAME->GetPlayerPos();

		if (playerPos.x > pMonster->GetPos().x)
			pMonster->SetDir(Vector(1, 0));
		else if(playerPos.x < pMonster->GetPos().x)
			pMonster->SetDir(Vector(-1, 0));
		else
			pMonster->SetDir(Vector(0, 0));

		if (playerPos.y > pMonster->GetPos().y)
			pMonster->SetDir(Vector(pMonster->GetDir().x, 1));
		else if (playerPos.y < pMonster->GetPos().y)
			pMonster->SetDir(Vector(pMonster->GetDir().x, -1));
		else
			pMonster->SetDir(Vector(pMonster->GetDir().x, 0));

		plusPos = (playerPos - pMonster->GetPos());
		coolTimeDT = (1 / DT);

	}

		pMonster->SetPos(
			pMonster->GetPos().x + (plusPos.x/coolTimeDT),
			pMonster->GetPos().y + (plusPos.y / coolTimeDT));
	
	
	coolTime += DT;

	if (coolTime >= 1)
	{
		coolTime = 0;
		pMonster->SetBehavior(MonsterBehavior::Idle);
	}
}

void CMonsterFly::Release()
{
}
