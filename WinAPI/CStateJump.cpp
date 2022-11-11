#include "framework.h"
#include "CStateJump.h"
#include "CPlayer.h"

CStateJump::~CStateJump()
{
}

void CStateJump::Init()
{
	coolTime = 0;
	farJump = false;
}

void CStateJump::Update()
{
	if (coolTime == 0)
	{
		pPlayer->m_vecPos.y--;
		pPlayer->SetGravity(-260);

		if (BUTTONSTAY(VK_SHIFT))
		{
			pPlayer->m_fSpeed = 200;
			if (BUTTONSTAY(VK_LEFT))
			{
				pPlayer->m_vecMoveDir.x = -1;
			}
			else if (BUTTONSTAY(VK_RIGHT))
			{
				pPlayer->m_vecMoveDir.x = 1;
			}
			farJump = true;
		}
	}
	coolTime += DT;

	if (farJump == true)
	{
		GAME->SetMp(-0.2);
		pPlayer->m_vecPos.x += (pPlayer->m_fSpeed * DT) * pPlayer->m_vecMoveDir.x;
		if (GAME->GetMp() < 1)
			pPlayer->m_behavior = Behavior::Idle;
	}
	else
	{
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


		if (BUTTONUP('Z'))
		{
			if (coolTime < 0.2)
			{
				pPlayer->SetGravity(-10);
			}
		}

		
	}
	if (pPlayer->GetGround() != 0 && coolTime > DT * 2)
	{
		coolTime = 0;
		farJump = false;
		pPlayer->m_behavior = Behavior::Idle;

		if (BUTTONSTAY(VK_LEFT) || BUTTONSTAY(VK_RIGHT))
		{
			pPlayer->m_behavior = Behavior::Walk;
		}
	}

	if (BUTTONDOWN('X') && !pPlayer->isThingCollision &&GAME->isItemSetting(L"¹æ¸ÁÀÌ"))
	{
		coolTime = 0;
		pPlayer->m_behavior = Behavior::AttackReady;
	}
}

void CStateJump::Render()
{
}

void CStateJump::Release()
{
}
