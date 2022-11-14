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
#include "CMonsterDamage.h"
#include "CItem.h"
#include "CCoin.h"

CFrog::CFrog()
{

	m_vecScale = Vector(20, 15);
	m_layer = Layer::Monster;
	m_fSpeed = 80;
	m_damageHp = 4;
	m_hp = 15;
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

	m_pImage = RESOURCE->LoadImg(L"Frog_Damage", L"Image\\Frog_Damage.png");

	m_pAnimator->CreateAnimation(L"Frog_Damage_Right", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.3f, 2, false);
	m_pAnimator->CreateAnimation(L"Frog_Damage_Left", m_pImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.3f, 2, false);

	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 1, m_vecScale.y - 1), Vector(0, 8));

	m_pAnimator->Play(L"Frog_Idle_Right", false);
	AddComponent(m_pAnimator);
	AddGravity(1);

	m_mapMonsterState.insert(make_pair(MonsterBehavior::Idle, new CMonsterIdle(this)));
	m_mapMonsterState.insert(make_pair(MonsterBehavior::Follow, new CMonsterFollow(this)));
	m_mapMonsterState.insert(make_pair(MonsterBehavior::Jump, new CMonsterJump(this)));
	m_mapMonsterState.insert(make_pair(MonsterBehavior::Damage, new CMonsterDamage(this)));


	m_behavior = MonsterBehavior::Idle;
}

void CFrog::Update()
{
	if (m_hp <= 0)
	{
		if (m_behavior == MonsterBehavior::Idle)
		{
			if (rand() % 3 == 0)
			{
				CItem* item = new CItem;
				item->SetPos(this->GetPos());
				item->SetItem(L"개구리 뒷다리");
				ADDOBJECT(item);
			}
			else if (rand() % 2 == 0)
			{
				CCoin* coin = new CCoin;
				coin->SetPos(this->GetPos());
				coin->SetDir(Vector(rand() % 3 - 1, 0));
				coin->SetPrice(rand() % 30 + 10);
				ADDOBJECT(coin);
			}
			DELETEOBJECT(this);
		}
	}

	if (m_vecPos.x > m_endX)
	{
		m_vecPos.x--;
		m_behavior = MonsterBehavior::Idle;
	}
	else if (m_vecPos.x < m_startX)
	{
		m_vecPos.x++;
		m_behavior = MonsterBehavior::Idle;
	}


	m_mapMonsterState.find(m_behavior)->second->Update();


	if (m_behavior == MonsterBehavior::Idle && GAME->GetPlayerPos().x > m_vecPos.x - 200 && GAME->GetPlayerPos().x < m_vecPos.x + 200)
	{
		if (rand()%500 == 1)m_behavior = MonsterBehavior::Jump;
	}

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
	if (pOtherCollider->GetObjName() == L"공격")
	{
		if (pOtherCollider->GetPos().x > m_vecPos.x)
			m_vecMoveDir.x = -1;
		else
			m_vecMoveDir.x = 1;
		m_behavior = MonsterBehavior::Damage;
	}
	else if (pOtherCollider->GetObjName() == L"플레이어")
	{
		GAME->SetHp(-m_damageHp);
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
	if (m_vecMoveDir.Length() > 0 && m_behavior != MonsterBehavior::Damage)
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

