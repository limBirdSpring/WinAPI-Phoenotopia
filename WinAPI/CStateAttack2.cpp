#include "framework.h"
#include "CStateAttack2.h"
#include "CPlayer.h"
#include "CAttack2.h"

CStateAttack2::~CStateAttack2()
{
}

void CStateAttack2::Init()
{
}

void CStateAttack2::Update()
{
	pPlayer->m_fSpeed = 100;
	if (coolTime == 0)
	{
		CAttack2* pAttack2 = new CAttack2();

		if (pPlayer->m_vecMoveDir.x == -1)
			pAttack2->SetPos(pPlayer->m_vecPos.x - 7, pPlayer->m_vecPos.y + 5);
		else if (pPlayer->m_vecMoveDir.x == 1)
			pAttack2->SetPos(pPlayer->m_vecPos.x + 7, pPlayer->m_vecPos.y + 5);
		pAttack2->SetPos(pPlayer->m_vecPos);
		ADDOBJECT(pAttack2);
	}
	coolTime += DT;

	if (coolTime > 0.66)
	{
		coolTime = 0;
		pPlayer->m_behavior = Behavior::Idle;
	}

	if (BUTTONSTAY(VK_LEFT))
	{
		pPlayer->m_vecPos.x += (pPlayer->m_fSpeed * DT) * -1;
	}
	else if (BUTTONSTAY(VK_RIGHT))
	{
		pPlayer->m_vecPos.x += (pPlayer->m_fSpeed * DT) * 1;
	}
}

void CStateAttack2::Render()
{
}

void CStateAttack2::Release()
{
}
