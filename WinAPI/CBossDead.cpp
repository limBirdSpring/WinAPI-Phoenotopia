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
	coolTime += DT;

	if (coolTime > 1.8)
	{
		CItem* item = new CItem;
		item->SetPos(pBoss->GetPos().x+30, pBoss->GetPos().y);
		item->SetItem(L"젬");
		ADDOBJECT(item);

		CItem* item2 = new CItem;
		item2->SetPos(pBoss->GetPos().x, pBoss->GetPos().y);
		item2->SetItem(L"엄청 비싸보이는 반지");
		ADDOBJECT(item2);
		DELETEOBJECT(pBoss);
	}
}

void CBossDead::Release()
{
}
