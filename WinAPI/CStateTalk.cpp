#include "framework.h"
#include "CStateTalk.h"
#include "CPlayer.h"
#include "CGameManager.h"

CStateTalk::CStateTalk(CPlayer* player)
{
	pPlayer = player;
}

CStateTalk::~CStateTalk()
{
}

void CStateTalk::Init()
{
	
}

void CStateTalk::Update()
{
	if (coolTime == 0)
	{
		pSe = RESOURCE->FindSound(L"Walk");
		SOUND->Stop(pSe);
	}

	if (!GAME->GetTalk())
	{
		pPlayer->m_behavior = Behavior::Idle;
	}
}

void CStateTalk::Render()
{
}

void CStateTalk::Release()
{
}
