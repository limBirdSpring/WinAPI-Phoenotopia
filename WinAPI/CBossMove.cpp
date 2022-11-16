#include "framework.h"
#include "CBossMove.h"
#include "CBoss.h"

CBossMove::~CBossMove()
{
}

void CBossMove::Init()
{
}

void CBossMove::Update()
{
	

	//if (coolTime == 0 || coolTime > 2 && coolTime < 2.1)
	if (GAME->GetPlayerPos().x > pBoss->GetPos().x+10 || GAME->GetPlayerPos().x < pBoss->GetPos().x - 10)
	{
		if (GAME->GetPlayerPos().x > pBoss->GetPos().x)
			pBoss->SetDir(Vector(1, 0));
		else
			pBoss->SetDir(Vector(-1, 0));
		pBoss->SetPos(pBoss->GetPos().x + DT * pBoss->GetSpeed() * pBoss->GetDir().x, pBoss->GetPos().y);
	}


	coolTime += DT;

	


	if (coolTime > 4)
	{
		coolTime = 0;

		if (rand()%2 == 0)
			pBoss->SetBehavior(BossBehavior::Attack);
		else
			pBoss->SetBehavior(BossBehavior::Attack2);
	}
}

void CBossMove::Release()
{
}
