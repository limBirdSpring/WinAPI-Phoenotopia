#include "framework.h"
#include "CStateDamage.h"
#include "CPlayer.h"

CStateDamage::~CStateDamage()
{
}

void CStateDamage::Init()
{
	coolTime = 0;
}

void CStateDamage::Update()
{
	//TODO : 더 섬세한 데미지 구현
	if (coolTime == 0)
	{
		pSe = RESOURCE->FindSound(L"PlayerDamage");
		SOUND->Play(pSe);
	}

	coolTime += DT;

	pPlayer->m_vecPos.x += (200.f * DT) * - pPlayer->m_vecMoveDir.x;

	if (coolTime > 0.2)
	{
		coolTime = 0;
		pPlayer->m_behavior = Behavior::Idle;
	}
}

void CStateDamage::Render()
{
}

void CStateDamage::Release()
{
}
