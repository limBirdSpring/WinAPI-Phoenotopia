#include "framework.h"
#include "CMonster.h"

#include "CRenderManager.h"
#include "CCollider.h"
#include "CEventManager.h"

CMonster::CMonster()
{
	m_strName = L"몬스터";
	m_vecScale = Vector(50, 50);
	m_layer = Layer::Monster;
	hp = 10;
}

CMonster::~CMonster()
{
}

void CMonster::Init()
{
	AddCollider(ColliderType::Rect, Vector(m_vecScale.x-1, m_vecScale.y - 1), Vector(0, 0));
	AddLineMove(m_vecPos, Vector(m_vecPos.x + 100, m_vecPos.y));
}

void CMonster::Update()
{
	if (hp < 0)
		DELETEOBJECT(this);
	
}

void CMonster::Render()
{
	RENDER->FrameRect(
		m_vecPos.x - m_vecScale.x * 0.5f,
		m_vecPos.y - m_vecScale.y * 0.5f,
		m_vecPos.x + m_vecScale.x * 0.5f,
		m_vecPos.y + m_vecScale.y * 0.5f);

}

void CMonster::Release()
{
}

void CMonster::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		Logger::Debug(L"몬스터가 플레이어와 충돌진입");
	}
	else if (pOtherCollider->GetObjName() == L"공격")
	{
		Logger::Debug(L"몬스터가 공격과 충돌진입");

		hp -= 5;
	}
}

void CMonster::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CMonster::OnCollisionExit(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		Logger::Debug(L"몬스터가 플레이어와 충돌해제");
	}
	else if (pOtherCollider->GetObjName() == L"미사일")
	{
		Logger::Debug(L"몬스터가 미사일과 충돌해제");
	}
}
