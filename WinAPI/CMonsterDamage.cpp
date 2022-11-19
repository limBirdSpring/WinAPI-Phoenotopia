#include "framework.h"
#include "CMonsterDamage.h"
#include "CMonster.h"

CMonsterDamage::~CMonsterDamage()
{
}

void CMonsterDamage::Init()
{
}

void CMonsterDamage::Update()
{
	Vector monPos = pMonster->GetPos();
	if (coolTime ==0)
	{
		pSe = RESOURCE->FindSound(L"Damage");
		SOUND->Play(pSe);
		
		if (pMonster->GetLayer() != Layer::FlyingMonster && pMonster->GetName() != L"PinkSlug")
		{
			pMonster->SetPos(monPos.x, --monPos.y);
			pMonster->SetGravity(-100);
		}
	}
	else if (coolTime > 0.5)
	{
		coolTime = 0;
		pMonster->SetBehavior(MonsterBehavior::Idle);
		return;
	}

	monPos.x += pMonster->GetDir().x * DT * 100;
	pMonster->SetPos(monPos.x, monPos.y);

	coolTime += DT;
}

void CMonsterDamage::Release()
{
}
