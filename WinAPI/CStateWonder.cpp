#include "framework.h"
#include "CStateWonder.h"
#include "CPlayer.h"

CStateWonder::CStateWonder(CPlayer* player)
{
	pPlayer = player;
}

CStateWonder::~CStateWonder()
{
}

void CStateWonder::Init()
{
}

void CStateWonder::Update()
{
	//coolTime += DT;
	//if (!GAME->GetTalk())
	//{
	//	coolTime = 0;
	//	pPlayer->m_behavior = Behavior::Idle;
	//}
	//else if (coolTime > 2)
	//{
	//	coolTime = 0;
	//	pPlayer->SetBehavior(Behavior::Talk);
	//}
}

void CStateWonder::Render()
{
}

void CStateWonder::Release()
{
}