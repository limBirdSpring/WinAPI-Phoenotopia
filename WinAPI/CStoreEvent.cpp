#include "framework.h"
#include "CStoreEvent.h"
#include "CPlayer.h"

CStoreEvent::~CStoreEvent()
{
}

void CStoreEvent::Init()
{
}

void CStoreEvent::Update()
{
	if (coolTime == 0)
	{
		CSound* pBgm = RESOURCE->FindSound(L"Panselo");
		SOUND->Stop(pBgm);
		pPlayer->SetBehavior(Behavior::Talk);
		pPlayer->SetPos(258, 398);
		GAME->SetTalk(true);
	}

	else if (coolTime > 1.5 && quest ==0)
	{
		quest++;
		pPlayer->SetBehavior(Behavior::Wonder);
	}
	else if (coolTime > 2.5 && quest == 1)
	{
		CSound* pSe = RESOURCE->FindSound(L"BBamm");
		SOUND->Play(pSe, 0.5);
		CAMERA->ZoomInOut(4);
		quest++;
	}
	else if (coolTime > 3 && quest == 2)
	{
		CSound* pSe = RESOURCE->FindSound(L"BBamm2");
		SOUND->Play(pSe, 0.5);
		CAMERA->ZoomInOut(5.5);
		quest++;
	}
	else if (coolTime > 3.5 && quest == 3)
	{
		CSound* pSe = RESOURCE->FindSound(L"BBamm3");
		SOUND->Play(pSe, 0.5);
		CAMERA->ZoomInOut(7);
		quest++;
	}
	else if (coolTime > 4.5)
	{
		GAME->mainQuest = MainQuest::VisitStore;
		CAMERA->ZoomInOut(3, 1);
		quest++;
		GAME->SetTalk(false);
		CSound* pBgm = RESOURCE->FindSound(L"Panselo");
		SOUND->Play(pBgm, 0.7);
		DELETEOBJECT(this);
	}


	coolTime += DT;
}

void CStoreEvent::Render()
{
	if (coolTime > 1)
	{
		RENDER->Text(L"еж~", 232, 366, 289, 404, Color(255,255,255,1), 40+ (quest>1?(quest*10):0));
	}
}

void CStoreEvent::Release()
{
}

void CStoreEvent::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CStoreEvent::Talk()
{
}
