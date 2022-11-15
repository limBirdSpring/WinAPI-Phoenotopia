#include "framework.h"
#include "CPinkSlug.h"

#include "CRenderManager.h"
#include "CCollider.h"
#include "CEventManager.h"
#include "CResourceManager.h"
#include "CAnimator.h"
#include "CGravity.h"
#include "CMonsterIdle.h"
#include "CMonsterDamage.h"

CPinkSlug::CPinkSlug()
{
	m_damageHp = 0;
	m_vecScale = Vector(30, 13);
	m_layer = Layer::Monster;
	m_strName = L"PinkSlug";
}

CPinkSlug::~CPinkSlug()
{
}

void CPinkSlug::Init()
{
	m_pImage = RESOURCE->LoadImg(L"PinkSlug", L"Image\\PinkSlug.png");

	m_pAnimator = new CAnimator;

	m_pAnimator->CreateAnimation(L"PinkSlug_Move", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.1f, 8);

	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 1, m_vecScale.y - 1), Vector(0, 8));
	AddLineMove(m_vecPos, Vector(m_vecPos.x + 100, m_vecPos.y), 10);

	m_pAnimator->Play(L"PinkSlug_Move", false);
	AddComponent(m_pAnimator);
	AddGravity(1);

	m_mapMonsterState.insert(make_pair(MonsterBehavior::Idle, new CMonsterIdle(this)));
	m_mapMonsterState.insert(make_pair(MonsterBehavior::Damage, new CMonsterDamage(this)));

	m_behavior = MonsterBehavior::Idle;
}

void CPinkSlug::Update()
{
	m_mapMonsterState.find(m_behavior)->second->Update();
}

void CPinkSlug::Render()
{

}

void CPinkSlug::Release()
{
}

void CPinkSlug::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		GAME->SetHp(-m_damageHp);
	}
	else if (pOtherCollider->GetObjName() == L"공격")
	{
		if (pOtherCollider->GetPos().x > m_vecPos.x)
			m_vecMoveDir.x = -1;
		else
			m_vecMoveDir.x = 1;
		m_behavior = MonsterBehavior::Damage;

	}
}

void CPinkSlug::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CPinkSlug::OnCollisionExit(CCollider* pOtherCollider)
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

