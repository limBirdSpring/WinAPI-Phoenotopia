#include "framework.h"
#include "CStateAttackReady.h"
#include "CPlayer.h"

CStateAttackReady::~CStateAttackReady()
{
}

void CStateAttackReady::Init()
{
	coolTime =0;
}

void CStateAttackReady::Update()
{
	//TODO : ���⸦ ������ ���� ���� �۵��ϰ� ����

	pPlayer->m_fSpeed = 50;

	if (BUTTONUP('X'))
	{
		coolTime = 0;
		if (pPlayer->GetGround() !=0)
			pPlayer->m_behavior = Behavior::Attack;
		else
			pPlayer->m_behavior = Behavior::Attack2;
	}

	if (coolTime > 1.5 && pPlayer->GetGround()!=0)
	{
		coolTime = 0;
		pSe = RESOURCE->FindSound(L"CriticalReady");
		SOUND->Play(pSe);
		pPlayer->m_behavior = Behavior::CriticalReady;
	}

	if (BUTTONSTAY(VK_LEFT))
	{
		pPlayer->m_vecMoveDir.x = -1;
		pPlayer->m_vecPos.x += (pPlayer->m_fSpeed * DT) * pPlayer->m_vecMoveDir.x;
	}
	else if (BUTTONSTAY(VK_RIGHT))
	{
		pPlayer->m_vecMoveDir.x = 1;
		pPlayer->m_vecPos.x += (pPlayer->m_fSpeed * DT) * pPlayer->m_vecMoveDir.x;
	}

	coolTime += DT;

}

void CStateAttackReady::Render()
{
}

void CStateAttackReady::Release()
{
}
