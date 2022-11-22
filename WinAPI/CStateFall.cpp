#include "framework.h"
#include "CStateFall.h"
#include "CPlayer.h"

CStateFall::~CStateFall()
{
}

void CStateFall::Init()
{
}

void CStateFall::Update()
{
	//TODO : 너무 높은곳에서 떨어졌을 경우 플레이어 잠시 멈춤

	pPlayer->m_fSpeed = 100;

	if (pPlayer->GetGround())
	{
		pPlayer->m_behavior = Behavior::Idle;
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

	if (BUTTONDOWN('X') && !pPlayer->isThingCollision && GAME->isItemSetting(L"방망이"))
	{
		coolTime = 0;
		pPlayer->m_behavior = Behavior::AttackReady;
	}

}

void CStateFall::Render()
{
}

void CStateFall::Release()
{
}
