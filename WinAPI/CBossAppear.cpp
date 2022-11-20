#include "framework.h"
#include "CBossAppear.h"
#include "CBoss.h"

CBossAppear::~CBossAppear()
{
}

void CBossAppear::Init()
{
}

void CBossAppear::Update()
{
	if (coolTime == 0)
	{
		pSe = RESOURCE->FindSound(L"BossAppear");
		SOUND->Play(pSe);
	}

	coolTime += DT;

	if (coolTime > 2)
		pBoss->SetBehavior(BossBehavior::Idle);
}

void CBossAppear::Release()
{
}
