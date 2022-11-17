#include "framework.h"
#include "CBossAppearBlock.h"
#include "CPlayer.h"
#include "CBoss.h"
#include "CPillarDoor.h"
#include "CStatue.h"

CBossAppearBlock::CBossAppearBlock(CPlayer* player)
{
	pPlayer = player;
	m_vecScale = Vector(10, 50);
	pDoor = nullptr;
}

CBossAppearBlock::~CBossAppearBlock()
{
}

void CBossAppearBlock::Init()
{
	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 0.1, m_vecScale.y - 0.1), Vector(0, 0));
}

void CBossAppearBlock::Update()
{
	if (coolTime > 3)
	{
		GAME->SetTalk(false);
		DELETEOBJECT(this);
	}
	else if(GAME->GetTalk())
	{
		coolTime += DT;
	}
}

void CBossAppearBlock::Render()
{
}

void CBossAppearBlock::Release()
{
}

void CBossAppearBlock::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		GAME->SetTalk(true);
		pPlayer->m_behavior = Behavior::Talk;
		ADDOBJECT(pBoss);
		if (pDoor != nullptr)
		{
			pDoor->pStatue->isStatueOn = true;
		}
	}
}

void CBossAppearBlock::OnCollisionExit(CCollider* pOtherCollider)
{
}

void CBossAppearBlock::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CBossAppearBlock::Talk()
{
}
