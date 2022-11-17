#include "framework.h"
#include "CStateWalk.h"
#include "CPlayer.h"

CStateWalk::CStateWalk(CPlayer* player)
{
	pPlayer = player;
}

CStateWalk::~CStateWalk()
{
}

void CStateWalk::Init()
{
}

void CStateWalk::Update()
{
	if (pPlayer->m_fSpeed ==30)
	{ }
	else if (pPlayer->m_fSpeed > 100)
		pPlayer->m_fSpeed -= 0.1;
	else if (pPlayer->m_fSpeed < 100)
		pPlayer->m_fSpeed = 100;


	if (pPlayer->GetGround() == 0)
		pPlayer->m_behavior = Behavior::Fall;

	if (BUTTONSTAY(VK_LEFT))
	{
		pPlayer->m_vecMoveDir.x = -1;
		pPlayer->m_vecPos.x += (pPlayer->m_fSpeed * DT) * pPlayer->m_vecMoveDir.x;
	}
	else if (BUTTONSTAY(VK_RIGHT))
	{
		pPlayer->m_vecMoveDir.x= 1;
		pPlayer->m_vecPos.x += (pPlayer->m_fSpeed * DT) * pPlayer->m_vecMoveDir.x;
	}
	else
	{
		pPlayer->m_behavior = Behavior::Idle;
	}

	if (BUTTONDOWN(VK_SHIFT))
	{
		pPlayer->m_behavior = Behavior::Run;
	}

	if (BUTTONDOWN('Z'))
	{
		pPlayer->m_behavior = Behavior::Jump;
	}

	else if (BUTTONDOWN(VK_DOWN))
	{
		pPlayer->m_behavior = Behavior::Down;
	}

	else if (BUTTONDOWN('X') && !pPlayer->isThingCollision && GAME->isItemSetting(L"¹æ¸ÁÀÌ"))
	{
		pPlayer->m_behavior = Behavior::AttackReady;
	}
	


}

void CStateWalk::Render()
{
}

void CStateWalk::Release()
{
}
