#include "framework.h"
#include "CSlug.h"

#include "CRenderManager.h"
#include "CCollider.h"
#include "CEventManager.h"
#include "CResourceManager.h"
#include "CAnimator.h"
#include "CGravity.h"

CSlug::CSlug()
{
	m_damageHp = 5;
	m_strName = L"Slug";
	m_vecScale = Vector(30, 13);
	m_layer = Layer::Monster;
}

CSlug::~CSlug()
{
}

void CSlug::Init()
{
	m_pImage = RESOURCE->LoadImg(L"Slug", L"Image\\Slug.png");

	m_pAnimator = new CAnimator;

	m_pAnimator->CreateAnimation(L"Slug_Move", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.1f, 8);

	AddCollider(ColliderType::Rect, Vector(m_vecScale.x-1, m_vecScale.y - 1), Vector(0, 8));
	AddLineMove(m_vecPos, Vector(m_vecPos.x + 100, m_vecPos.y), 10);

	m_pAnimator->Play(L"Slug_Move", false);
	AddComponent(m_pAnimator);
	AddGravity(1);
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
	if (pOtherCollider->GetObjName() == L"�÷��̾�")
	{
		GAME->SetHp(-m_damageHp);
	}
	else if (pOtherCollider->GetObjName() == L"����")
	{
		Logger::Debug(L"���Ͱ� ���ݰ� �浹����");
		pSe = RESOURCE->FindSound(L"SlugDamage");
		SOUND->Play(pSe);
	}
}

void CSlug::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CSlug::OnCollisionExit(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"�÷��̾�")
	{
		Logger::Debug(L"���Ͱ� �÷��̾�� �浹����");
	}
	else if (pOtherCollider->GetObjName() == L"�̻���")
	{
		Logger::Debug(L"���Ͱ� �̻��ϰ� �浹����");
	}
}

