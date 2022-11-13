#include "framework.h"
#include "CStatePush.h"
#include "CPlayer.h"

CStatePush::~CStatePush()
{
}

void CStatePush::Init()
{
}

void CStatePush::Update()
{

	if (pPlayer->GetGround() == 0)
	{
		pPlayer->m_fSpeed = 100;
		pPlayer->m_behavior = Behavior::Fall;
	}

	if (BUTTONSTAY('A'))
		pPlayer->m_vecPos.x += (pPlayer->m_fSpeed * DT) * pPlayer->m_vecMoveDir.x;
	
	
	if (BUTTONUP('A'))
	{
		pPlayer->m_fSpeed = 100;
		pPlayer->m_behavior = Behavior::Idle;
	}

}

void CStatePush::Render()
{
}

void CStatePush::Release()
{
}
