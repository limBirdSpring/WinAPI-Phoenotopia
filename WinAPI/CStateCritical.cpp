#include "framework.h"
#include "CStateCritical.h"
#include "CPlayer.h"
#include "CCritical.h"

CStateCritical::~CStateCritical()
{
}

void CStateCritical::Init()
{
}

void CStateCritical::Update()
{
	if (coolTime == 0)
	{
		pSe = RESOURCE->FindSound(L"Critical2");
		SOUND->Play(pSe);

		CCritical* pCritical = new CCritical();

		if (pPlayer->m_vecMoveDir.x == -1)
			pCritical->SetPos(pPlayer->m_vecPos.x, pPlayer->m_vecPos.y);
		else if (pPlayer->m_vecMoveDir.x == 1)
			pCritical->SetPos(pPlayer->m_vecPos.x, pPlayer->m_vecPos.y);
		pCritical->SetPos(pPlayer->m_vecPos);
		ADDOBJECT(pCritical);
	}
	coolTime += DT;

	if (coolTime > 1)
	{
		coolTime = 0;
		pPlayer->m_behavior = Behavior::Idle;
	}


}

void CStateCritical::Render()
{
}

void CStateCritical::Release()
{
}
