#include "framework.h"
#include "CBossDead.h"
#include "CBoss.h"
#include "CItem.h"

CBossDead::~CBossDead()
{
}

void CBossDead::Init()
{
}

void CBossDead::Update()
{
	if (coolTime == 0)
	{
		pSe = RESOURCE->FindSound(L"BossBattle");
		SOUND->Stop(pSe);
		pSe = RESOURCE->FindSound(L"BossDead");
		SOUND->Play(pSe);
	}

	coolTime += DT;

	if (coolTime > 1.8)
	{
		

		CItem* item = new CItem;
		item->SetPos(pBoss->GetPos().x+30, pBoss->GetPos().y);
		item->SetItem(L"��");
		ADDOBJECT(item);

		CItem* item2 = new CItem;
		item2->SetPos(pBoss->GetPos().x, pBoss->GetPos().y);
		item2->SetItem(L"��û ��κ��̴� ����");
		ADDOBJECT(item2);
		DELETEOBJECT(pBoss);
	}
}

void CBossDead::Release()
{
}
