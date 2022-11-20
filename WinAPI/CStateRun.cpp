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
	if (coolTime == 0)
	{
		pSe = RESOURCE->FindSound(L"PlayerRun");
		SOUND->Play(pSe,0.5, false);
		dir = pPlayer->GetDir().x;
	}

	coolTime += DT;

	GAME->SetMp(-0.2);

	if (GAME->GetMp() < 1)
	{

		coolTime = 0;
		pSe = RESOURCE->FindSound(L"PlayerRun");
		SOUND->Stop(pSe);
		pPlayer->m_behavior = Behavior::Walk;
	}


	if (pPlayer->GetGround() == 0)
	{
		coolTime = 0;
		pSe = RESOURCE->FindSound(L"PlayerRun");
		SOUND->Stop(pSe);
		pPlayer->m_behavior = Behavior::Fall;
	}


	if (dir == 1)
	{
		if (BUTTONSTAY(VK_RIGHT))
		{
			if (pPlayer->m_vecMoveDir.x == -1)
			{
				coolTime = 0;
				pSe = RESOURCE->FindSound(L"PlayerRun");
				SOUND->Stop(pSe);
				pPlayer->m_behavior = Behavior::Idle;
			}
			else
			{
				if (pPlayer->m_fSpeed < 200)
					pPlayer->m_fSpeed += 0.2;


				pPlayer->m_vecPos.x += (pPlayer->m_fSpeed * DT) * pPlayer->m_vecMoveDir.x;
			}
		}
		else if (BUTTONSTAY(VK_LEFT))
		{
			pPlayer->m_vecMoveDir.x = -1;
			pPlayer->m_fSpeed -= pPlayer->m_fSpeed *3*DT;
			pPlayer->m_vecPos.x += (pPlayer->m_fSpeed * DT) * -1;
		}
		else
		{
			coolTime = 0;
			pSe = RESOURCE->FindSound(L"PlayerRun");
			SOUND->Stop(pSe);
			pPlayer->m_behavior = Behavior::Idle;
		}
	}
	else if (dir == -1)
	{
		if (BUTTONSTAY(VK_LEFT))
		{
			if (pPlayer->m_vecMoveDir.x == 1)
			{
				coolTime = 0;
				pSe = RESOURCE->FindSound(L"PlayerRun");
				SOUND->Stop(pSe);
				pPlayer->m_behavior = Behavior::Idle;
			}
			else
			{
				if (pPlayer->m_fSpeed < 200)
					pPlayer->m_fSpeed += 0.2;


				pPlayer->m_vecPos.x += (pPlayer->m_fSpeed * DT) * pPlayer->m_vecMoveDir.x;
			}
		}
		else if (BUTTONSTAY(VK_RIGHT))
		{
			pPlayer->m_vecMoveDir.x = 1;
			pPlayer->m_fSpeed -= pPlayer->m_fSpeed *3 * DT;
			pPlayer->m_vecPos.x += (pPlayer->m_fSpeed * DT) * 1;
		}
		else
		{
			coolTime = 0;
			pSe = RESOURCE->FindSound(L"PlayerRun");
			SOUND->Stop(pSe);
			pPlayer->m_behavior = Behavior::Idle;
		}

	}

	

	if (BUTTONUP(VK_SHIFT))
	{
		coolTime = 0;
		pSe = RESOURCE->FindSound(L"PlayerRun");
		SOUND->Stop(pSe);
		pPlayer->m_behavior = Behavior::Walk;
	}

	if (BUTTONDOWN('Z'))
	{
		coolTime = 0;
		pSe = RESOURCE->FindSound(L"PlayerRun");
		SOUND->Stop(pSe);
		pPlayer->m_behavior = Behavior::Jump;
	}


	if (pPlayer->m_fSpeed < 10)
	{
		coolTime = 0;
		pSe = RESOURCE->FindSound(L"PlayerRun");
		SOUND->Stop(pSe);
		pPlayer->m_behavior = Behavior::Walk;
	}
}

void CStateRun::Render()
{
}

void CStateRun::Release()
{
}
