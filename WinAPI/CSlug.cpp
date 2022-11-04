#include "framework.h"
#include "CSlug.h"

#include "CRenderManager.h"
#include "CCollider.h"
#include "CEventManager.h"
#include "CResourceManager.h"
#include "CAnimator.h"

CSlug::CSlug()
{
	m_strName = L"Slug";
	m_vecScale = Vector(30, 13);
	m_layer = Layer::Monster;
}

CSlug::~CSlug()
{
}

void CSlug::Init()
{
	m_pMoveImage = RESOURCE->LoadImg(L"Slug", L"Image\\Slug.png");

	m_pAnimator = new CAnimator;

	m_pAnimator->CreateAnimation(L"Slug_Move", m_pMoveImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.1f, 8);

	AddCollider(ColliderType::Rect, Vector(m_vecScale.x-1, m_vecScale.y - 1), Vector(0, 8));
	AddLineMove(m_vecPos, Vector(m_vecPos.x + 100, m_vecPos.y), 30);

	m_pAnimator->Play(L"Slug_Move", false);
	AddComponent(m_pAnimator);
}

void CSlug::Update()
{
	
}

void CSlug::Render()
{

}

void CSlug::Release()
{
}

void CSlug::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		Logger::Debug(L"몬스터가 플레이어와 충돌진입");
	}
	else if (pOtherCollider->GetObjName() == L"공격")
	{
		Logger::Debug(L"몬스터가 공격과 충돌진입");

	}
}

void CSlug::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CSlug::OnCollisionExit(CCollider* pOtherCollider)
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

