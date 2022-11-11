#include "framework.h"
#include "CStateAttack.h"
#include "CPlayer.h"
#include "CAttack.h"

CStateAttack::~CStateAttack()
{
}

void CStateAttack::Init()
{
	coolTime = 0;
}

void CStateAttack::Update()
{
	if (coolTime == 0)
	{
		CAttack* pAttack = new CAttack();

		if (pPlayer->m_vecMoveDir.x == -1)
			pAttack->SetPos(pPlayer->m_vecPos.x - 10, pPlayer->m_vecPos.y + 7);
		else if (pPlayer->m_vecMoveDir.x == 1)
			pAttack->SetPos(pPlayer->m_vecPos.x + 10, pPlayer->m_vecPos.y + 7);
		pAttack->SetPos(pPlayer->m_vecPos);
		ADDOBJECT(pAttack);
	}
	coolTime += DT;

	if (coolTime > 0.5)
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

void CStateAttack::Render()
{
}

void CStateAttack::Release()
{
}
