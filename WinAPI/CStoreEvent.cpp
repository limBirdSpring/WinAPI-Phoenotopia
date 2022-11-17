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
		pPlayer->SetBehavior(Behavior::Talk);
		pPlayer->SetPos(268, 398);
		GAME->SetTalk(true);
	}

	else if (coolTime > 1.5 && quest ==0)
	{
		quest++;
		pPlayer->SetBehavior(Behavior::Wonder);
	}
	else if (coolTime > 2.5 && quest == 1)
	{
		quest++;
		CAMERA->ZoomInOut(4);
	}
	else if (coolTime > 3 && quest == 2)
	{
		quest++;
		CAMERA->ZoomInOut(5.5);
	}
	else if (coolTime > 3.5 && quest == 3)
	{
		quest++;
		CAMERA->ZoomInOut(7);
	}
	else if (coolTime > 4.5)
	{
		GAME->mainQuest = MainQuest::VisitStore;
		quest++;
		CAMERA->ZoomInOut(3, 1);
		GAME->SetTalk(false);
		DELETEOBJECT(this);
	}


	coolTime += DT;
}

void CStoreEvent::Render()
{
	if (coolTime > 1)
	{
		RENDER->Text(L"еж~", 232, 366, 289, 404, Color(255,255,255,1), 40+ (quest>2?(quest*10):0));
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
