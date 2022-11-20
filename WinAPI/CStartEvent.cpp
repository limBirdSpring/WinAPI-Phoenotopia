#include "framework.h"
#include "CStartEvent.h"
#include "CImageBox.h"
#include "CPlayer.h"

CStartEvent::CStartEvent(CPlayer* player)
{
	 pPlayer = player; 
	 cake = false; 
}

CStartEvent::~CStartEvent()
{
}

void CStartEvent::Init()
{
	
}

void CStartEvent::Update()
{
	if (coolTime == 0)
	{
		GAME->SetTalk(true);
		pPlayer->SetBehavior(Behavior::Bored);
	
	}

	
	else if (coolTime > 2 && cake == false)
	{
		CSound* pSe = RESOURCE->FindSound(L"Dialogue");
		SOUND->Play(pSe, 0.5);
		cake = true;
		pCake = new CImageBox;
		pPlayer->SetBehavior(Behavior::Talk);
		pCake->pEventImage = RESOURCE->LoadImg(L"Wanna_Cake", L"Image\\Wanna_Cake.png");
		ADDOBJECT(pCake);
	}

	else if (coolTime > 4)
	{
		DELETEOBJECT(pCake);
		GAME->SetTalk(false);
		DELETEOBJECT(this);
	}

	coolTime += DT;
}

void CStartEvent::Render()
{
}

void CStartEvent::Release()
{
}

void CStartEvent::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CStartEvent::Talk()
{
}
