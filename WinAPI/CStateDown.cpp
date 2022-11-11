#include "framework.h"
#include "CStateDown.h"
#include "CPlayer.h"

CStateDown::~CStateDown()
{
}

void CStateDown::Init()
{
}

void CStateDown::Update()
{
	if (pPlayer->GetPlatform() != 0 && BUTTONDOWN('Z'))
	{
		pPlayer->m_behavior = Behavior::DownJump;
	}


	if (BUTTONUP(VK_DOWN))
	{
		if (BUTTONDOWN(VK_LEFT) || BUTTONDOWN(VK_RIGHT) || BUTTONSTAY(VK_LEFT) || BUTTONSTAY(VK_RIGHT))
		{
			pPlayer->m_behavior = Behavior::Walk;
		}
		else
			pPlayer->m_behavior = Behavior::Idle;
	}

	
}

void CStateDown::Render()
{

}

void CStateDown::Release()
{
}
