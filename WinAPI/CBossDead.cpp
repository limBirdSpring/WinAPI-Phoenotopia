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
		item->SetPos(pBoss->GetPos());
		item->SetItem(L"��Ʈ�� ������");
		ADDOBJECT(item);

		CItem* item2 = new CItem;
		item2->SetPos(pBoss->GetPos().x + 10, pBoss->GetPos().y);
		item2->SetItem(L"��û ��κ��̴� ����");
		ADDOBJECT(item2);
		DELETEOBJECT(pBoss);
	}
}

void CBossDead::Release()
{
}
