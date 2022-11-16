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
	coolTime += DT;

	if (coolTime > 2)
		pBoss->SetBehavior(BossBehavior::Idle);
}

void CBossAppear::Release()
{
}
