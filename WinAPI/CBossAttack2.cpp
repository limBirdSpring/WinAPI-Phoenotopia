#include "framework.h"
#include "CBossAttack2.h"
#include "CBossSkill.h"
#include "CBoss.h"

CBossAttack2::~CBossAttack2()
{
}

void CBossAttack2::Init()
{
}

void CBossAttack2::Update()
{
	
	if (coolTime ==0)
	{
		CBossSkill* pBossSkill = new CBossSkill;
		//pBossSkill->SetPos((pBoss->GetPos().x + 80) * pBoss->GetDir().x, pBoss->GetPos().y);
		pBossSkill->SetPos(pBoss->GetPos());
		pBossSkill->SetScale(250, 100);
		pBossSkill->damage = 8;
		pBossSkill->coolTime = 1.2;
		pBossSkill->idleTime = 1.0;
		ADDOBJECT(pBossSkill);
	}
	coolTime += DT;

	if (coolTime > 2.5)
	{
		coolTime = 0;
		pBoss->SetBehavior(BossBehavior::Idle);
	}
	
}

void CBossAttack2::Release()
{
}
