#include "framework.h"
#include "CFrog.h"

#include "CRenderManager.h"
#include "CCollider.h"
#include "CEventManager.h"
#include "CResourceManager.h"
#include "CAnimator.h"
#include "CGravity.h"
#include "CMonsterFollow.h"
#include "CMonster.h"
#include "CMonsterIdle.h"
#include "CMonsterMove.h"
#include "CMonsterJump.h"

CFrog::CFrog()
{

	m_vecScale = Vector(20, 15);
	m_layer = Layer::Monster;
	m_fSpeed = 80;
	m_damageHp = 4;
}

CFrog::~CFrog()
{
}

void CFrog::Init()
{
	srand(time(NULL));
	m_pAnimator = new CAnimator;

	m_pImage = RESOURCE->LoadImg(L"Frog_Idle", L"Image\\Frog_Idle.png");

	m_pAnimator->CreateAnimation(L"Frog_Idle_Right", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.2f, 4);
	m_pAnimator->CreateAnimation(L"Frog_Idle_Left", m_pImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.2f, 4);

	m_pImage = RESOURCE->LoadImg(L"Frog_Jump", L"Image\\Frog_Jump.png");

	m_pAnimator->CreateAnimation(L"Frog_Jump_Right", m_pImage, Vector(150, 0), Vector(100, 100), Vector(150, 0), 0.3f, 2);
	m_pAnimator->CreateAnimation(L"Frog_Jump_Left", m_pImage, Vector(150, 150), Vector(100, 100), Vector(150, 0), 0.3f, 2);

	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 1, m_vecScale.y - 1), Vector(0, 8));

	m_pAnimator->Play(L"Frog_Idle_Right", false);
	AddComponent(m_pAnimator);
	AddGravity(1);

	m_mapMonsterState.insert(make_pair(MonsterBehavior::Idle, new CMonsterIdle(this)));
	m_mapMonsterState.insert(make_pair(MonsterBehavior::Follow, new CMonsterFollow(this)));
	m_mapMonsterState.insert(make_pair(MonsterBehavior::Jump, new CMonsterJump(this)));

	m_behavior = MonsterBehavior::Idle;
}

void CFrog::Update()
{
	m_mapMonsterState.find(m_behavior)->second->Update();

	int random = rand() % 500;
	if (m_behavior == MonsterBehavior::Idle && random == 1)
		m_behavior = MonsterBehavior::Jump;

	AnimatorUpdate();
}

void CFrog::Render()
{

}

void CFrog::Release()
{
}

void CFrog::OnCollisionEnter(CCollider* pOtherCollider)
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

void CFrog::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CFrog::OnCollisionExit(CCollider* pOtherCollider)
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

void CFrog::AnimatorUpdate()
{
	if (m_vecMoveDir.Length() > 0)
		m_vecLookDir = m_vecMoveDir;

	wstring str = L"Frog";

	switch (m_behavior)
	{
	case MonsterBehavior::Follow: str += L"_Jump";
		break;
	case MonsterBehavior::Jump: str += L"_Jump";
		break;
	case MonsterBehavior::Damage: str += L"_Damage";
		break;
	default: str += L"_Idle";
	}

	if (m_vecLookDir.x > 0) str += L"_Right";
	else if (m_vecLookDir.x <= 0) str += L"_Left";

	m_pAnimator->Play(str, false);
}

