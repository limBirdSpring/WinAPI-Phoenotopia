#include "framework.h"
#include "CStateIdle.h"
#include "CPlayer.h"



CStateIdle::~CStateIdle()
{
}

void CStateIdle::Init()
{
}

void CStateIdle::Update()
{
	pPlayer->m_fSpeed = 100;

	if (pPlayer->GetGround() ==0)
		pPlayer->m_behavior = Behavior::Fall;

	if (BUTTONSTAY(VK_LEFT))
	{
		pPlayer->m_vecMoveDir.x = -1;
		pPlayer->m_behavior = Behavior::Walk;
	}
	else if (BUTTONSTAY(VK_RIGHT))
	{
		pPlayer->m_vecMoveDir.x = 1;
		pPlayer->m_behavior = Behavior::Walk;
	}
	else if (BUTTONSTAY('Z'))
	{
		pPlayer->m_behavior = Behavior::Jump;
	}
	else if (BUTTONDOWN(VK_DOWN))
	{
		pPlayer->m_behavior = Behavior::Down;
	}
	else if (BUTTONDOWN('X'))
	{
		pPlayer->m_behavior = Behavior::AttackReady;
	}
}

void CStateIdle::Render()
{
}

void CStateIdle::Release()
{
}
