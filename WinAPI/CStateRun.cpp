#include "framework.h"
#include "CStateRun.h"
#include "CPlayer.h"

CStateRun::~CStateRun()
{
}

void CStateRun::Init()
{
	
}

void CStateRun::Update()
{
	//TODO : 방향 틀 때 속도 줄어들며 멈춤, 체력바가 다 닳으면 점차 속도가 줄며 walk로 이동

	pPlayer->m_fSpeed = 200;

	if (pPlayer->GetGround() == 0)
		pPlayer->m_behavior = Behavior::Fall;

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
	else
	{
		pPlayer->m_behavior = Behavior::Idle;
	}

	if (BUTTONUP(VK_SHIFT))
	{
		pPlayer->m_behavior = Behavior::Walk;
	}

	if (BUTTONDOWN('Z'))
	{
		pPlayer->m_behavior = Behavior::Jump;
	}
}

void CStateRun::Render()
{
}

void CStateRun::Release()
{
}
