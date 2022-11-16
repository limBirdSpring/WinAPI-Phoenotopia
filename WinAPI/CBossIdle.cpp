#include "framework.h"
#include "CBossIdle.h"
#include "CBoss.h"

CBossIdle::~CBossIdle()
{
}

void CBossIdle::Init()
{
}

void CBossIdle::Update()
{
	coolTime += DT;
	if (coolTime > 2)
	{
		coolTime = 0;
		pBoss->SetBehavior(BossBehavior::Move);
	}
}

void CBossIdle::Release()
{
}
