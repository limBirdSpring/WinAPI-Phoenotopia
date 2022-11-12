#include "framework.h"
#include "CStateCriticalReady.h"
#include "CPlayer.h"

CStateCriticalReady::~CStateCriticalReady()
{
}

void CStateCriticalReady::Init()
{
}

void CStateCriticalReady::Update()
{
	pPlayer->m_fSpeed = 50;

	if (BUTTONUP('X'))
	{
		coolTime = 0;
		pPlayer->m_behavior = Behavior::Critical;
	}
	if (BUTTONSTAY(VK_LEFT))
	{
		pPlayer->m_vecMoveDir.x = -1;
		
	}
	else if (BUTTONSTAY(VK_RIGHT))
	{
		pPlayer->m_vecMoveDir.x = 1;
		
	}

	coolTime += DT;
}

void CStateCriticalReady::Render()
{
}

void CStateCriticalReady::Release()
{
}
