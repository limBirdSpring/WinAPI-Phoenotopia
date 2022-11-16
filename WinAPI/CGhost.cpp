#include "framework.h"
#include "CGhost.h"

#include "CRenderManager.h"
#include "CCollider.h"
#include "CEventManager.h"
#include "CResourceManager.h"
#include "CAnimator.h"
#include "CGravity.h"
#include "CBossAppear.h"
#include "CBoss.h"
#include "CBossIdle.h"
#include "CBossMove.h"
#include "CBossDead.h"
#include "CBossAttack.h"
#include "CBossAttack2.h"
#include "CItem.h"
#include "CCoin.h"

CGhost::CGhost()
{

	m_vecScale = Vector(20, 15);
	m_layer = Layer::Boss;
	m_fSpeed = 120;
	m_vecMoveDir.x = 0;
	m_damageHp = 4;
	m_hp = 15;
}

CGhost::~CGhost()
{
}

void CGhost::Init()
{
	srand(time(NULL));
	m_pAnimator = new CAnimator;

	m_pImage = RESOURCE->LoadImg(L"Boss_Idle", L"Image\\Boss_Idle.png");

	m_pAnimator->CreateAnimation(L"Boss_Idle_Right", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.2f, 4);
	m_pAnimator->CreateAnimation(L"Boss_Idle_Left", m_pImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.2f, 4);

	m_pImage = RESOURCE->LoadImg(L"Boss_Move", L"Image\\Boss_Move.png");

	m_pAnimator->CreateAnimation(L"Boss_Move_Left", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.2f, 7);
	m_pAnimator->CreateAnimation(L"Boss_Move_Right", m_pImage, Vector(900, 150), Vector(100, 100), Vector(-150, 0), 0.2f, 7);

	m_pImage = RESOURCE->LoadImg(L"Boss_Dead", L"Image\\Boss_Dead.png");

	m_pAnimator->CreateAnimation(L"Boss_Dead_Left", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.2f, 9, false);
	m_pAnimator->CreateAnimation(L"Boss_Dead_Right", m_pImage, Vector(1200, 150), Vector(100, 100), Vector(-150, 0), 0.2f, 9, false);

	m_pImage = RESOURCE->LoadImg(L"Boss_Appear", L"Image\\Boss_Appear.png");

	m_pAnimator->CreateAnimation(L"Boss_Appear_Left", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.2f, 10, false);
	m_pAnimator->CreateAnimation(L"Boss_Appear_Right", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.2f, 10, false);

	m_pImage = RESOURCE->LoadImg(L"Boss_Attack", L"Image\\Boss_Attack.png");

	m_pAnimator->CreateAnimation(L"Boss_Attack_Left", m_pImage, Vector(0, 0), Vector(200, 200), Vector(300, 0), 0.2f, 9, false);
	m_pAnimator->CreateAnimation(L"Boss_Attack_Right", m_pImage, Vector(2400, 300), Vector(200, 200), Vector(-300, 0), 0.2f, 9, false);

	m_pImage = RESOURCE->LoadImg(L"Boss_Attack2", L"Image\\Boss_Attack2.png");

	m_pAnimator->CreateAnimation(L"Boss_Attack2_Left", m_pImage, Vector(0, 0), Vector(400, 200), Vector(614, 0), 0.2f, 15, false);
	m_pAnimator->CreateAnimation(L"Boss_Attack2_Right", m_pImage, Vector(8600, 300), Vector(400, 200), Vector(-614, 0), 0.2f, 15, false);


	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 1, m_vecScale.y - 1), Vector(0, 8));

	m_pAnimator->Play(L"Boss_Appear_Left", false);
	AddComponent(m_pAnimator); 
	AddGravity(1);

	m_mapBossState.insert(make_pair(BossBehavior::Appear, new CBossAppear(this)));
	m_mapBossState.insert(make_pair(BossBehavior::Idle, new CBossIdle(this)));
	m_mapBossState.insert(make_pair(BossBehavior::Move, new CBossMove(this)));
	m_mapBossState.insert(make_pair(BossBehavior::Attack, new CBossAttack(this)));
	m_mapBossState.insert(make_pair(BossBehavior::Attack2, new CBossAttack2(this)));
	m_mapBossState.insert(make_pair(BossBehavior::Dead, new CBossDead(this)));


	m_behavior = BossBehavior::Appear;
}

void CGhost::Update()
{
	m_mapBossState.find(m_behavior)->second->Update();
	AnimatorUpdate();

}

void CGhost::Render()
{

}

void CGhost::Release()
{
}

void CGhost::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"공격")
	{
		if (pOtherCollider->GetPos().x > m_vecPos.x)
			m_vecMoveDir.x = -1;
		else
			m_vecMoveDir.x = 1;
	
	}
	else if (pOtherCollider->GetObjName() == L"플레이어")
	{
		GAME->SetHp(-m_damageHp);
	}
}

void CGhost::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CGhost::OnCollisionExit(CCollider* pOtherCollider)
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

void CGhost::AnimatorUpdate()
{
	if (m_vecMoveDir.Length() > 0)
		m_vecLookDir = m_vecMoveDir;
	
	wstring str = L"Boss";

	switch (m_behavior)
	{
	case BossBehavior::Move: str += L"_Move";
		break;
	case BossBehavior::Attack: str += L"_Attack";
		break;
	case BossBehavior::Attack2: str += L"_Attack2";
		break;
	case BossBehavior::Appear: str += L"_Appear";
		break;
	case BossBehavior::Dead: str += L"_Dead";
		break;
	default: str += L"_Idle";
	}

	if (m_vecLookDir.x > 0) str += L"_Right";
	else if (m_vecLookDir.x <= 0) str += L"_Left";

	m_pAnimator->Play(str, false);
}

