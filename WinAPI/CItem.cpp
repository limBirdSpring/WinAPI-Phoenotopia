#include "framework.h"
#include "CItem.h"
#include "CCollider.h"
#include "CGravity.h"

CItem::CItem()
{
	m_vecScale = Vector(10, 10);
}

CItem::~CItem()
{
}

void CItem::Init()
{
	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 1, m_vecScale.y - 1), Vector(0, 0));
	//AddGravity(1);
}

void CItem::Update()
{
}

void CItem::Render()
{
	RENDER->Image(item.img, m_vecPos.x - 25, m_vecPos.y - 25, m_vecPos.x + 25, m_vecPos.y + 25);
}

void CItem::Release()
{
}

void CItem::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		GAME->PushBackInvenItem(item);
		DELETEOBJECT(this);
	}
}

void CItem::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CItem::OnCollisionExit(CCollider* pOtherCollider)
{
}
