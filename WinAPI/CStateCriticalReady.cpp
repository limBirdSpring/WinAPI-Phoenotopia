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


	coolTime += DT;
}

void CStateCriticalReady::Render()
{
}

void CStateCriticalReady::Release()
{
}
