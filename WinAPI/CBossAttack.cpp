#include "framework.h"
#include "CBossAttack.h"
#include "CBossSkill.h"
#include "CBoss.h"

CBossAttack::~CBossAttack()
{
}

void CBossAttack::Init()
{
}

void CBossAttack::Update()
{
	
	if (coolTime == 0)
	{
		CBossSkill* pBossSkill = new CBossSkill;
		pBossSkill->SetPos(pBoss->GetPos());
		pBossSkill->SetScale(100, 100);
		pBossSkill->damage = 8;
		pBossSkill->coolTime = 0.5;
		pBossSkill->idleTime = 0.5;
		ADDOBJECT(pBossSkill);
	}
	coolTime += DT;

	if (coolTime > 2.0)
	{
		coolTime = 0;
		pBoss->SetBehavior(BossBehavior::Idle);
	}

	
}

void CBossAttack::Release()
{
}
