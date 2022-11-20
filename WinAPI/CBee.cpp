#include "framework.h"
#include "CBee.h"

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
#include "CMonsterFly.h"
#include "CMonsterDamage.h"
#include "CItem.h"
#include "CCoin.h"

CBee::CBee()
{

	m_vecScale = Vector(20, 15);
	m_layer = Layer::FlyingMonster;
	m_fSpeed = 80;
	m_damageHp = 3;
	m_hp = 15;
}

CBee::~CBee()
{
}

void CBee::Init()
{
	srand(time(NULL));
	m_pAnimator = new CAnimator;

	m_pImage = RESOURCE->LoadImg(L"Bee", L"Image\\Bee.png");

	m_pAnimator->CreateAnimation(L"Bee_Left", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.2f, 4);
	m_pAnimator->CreateAnimation(L"Bee_Right", m_pImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.2f, 4);

	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 1, m_vecScale.y - 1), Vector(0, 0));

	m_pAnimator->Play(L"Bee_Right", false);
	AddComponent(m_pAnimator);

	m_mapMonsterState.insert(make_pair(MonsterBehavior::Idle, new CMonsterIdle(this)));
	m_mapMonsterState.insert(make_pair(MonsterBehavior::Fly, new CMonsterFly(this)));
	m_mapMonsterState.insert(make_pair(MonsterBehavior::Damage, new CMonsterDamage(this)));


	m_behavior = MonsterBehavior::Idle;
}

void CBee::Update()
{
	if (m_hp <= 0)
	{

			if (rand() % 3 == 0)
			{
				CItem* item = new CItem;
				item->SetPos(this->GetPos());
				item->SetItem(L"벌꿀");
				ADDOBJECT(item);
			}
			else if (rand() % 2 == 0)
			{
				CCoin* coin = new CCoin;
				coin->SetPos(this->GetPos());
				coin->SetDir(Vector(rand() % 3 - 1, 0));
				coin->SetPrice(rand() % 50 + 10);
				ADDOBJECT(coin);
			}
			DELETEOBJECT(this);
		
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

	

	if (m_behavior == MonsterBehavior::Idle && GAME->GetPlayerPos().x > m_vecPos.x - 100 && GAME->GetPlayerPos().x < m_vecPos.x + 100 && GAME->GetPlayerPos().y > m_vecPos.y - 100 && GAME->GetPlayerPos().y < m_vecPos.y + 100)
	{
		m_behavior = MonsterBehavior::Fly;
		pSe = RESOURCE->FindSound(L"Bee");
		if (!pSe->IsPlaying())
			SOUND->Play(pSe, 1, false);
	}

	AnimatorUpdate();
}

void CBee::Render()
{

}

void CBee::Release()
{
}

void CBee::OnCollisionEnter(CCollider* pOtherCollider)
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

void CBee::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CBee::OnCollisionExit(CCollider* pOtherCollider)
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

void CBee::AnimatorUpdate()
{
	if (m_vecMoveDir.Length() > 0 && m_behavior != MonsterBehavior::Damage)
		m_vecLookDir = m_vecMoveDir;

	wstring str = L"Bee";

	if (m_vecLookDir.x > 0) str += L"_Right";
	else if (m_vecLookDir.x <= 0) str += L"_Left";

	m_pAnimator->Play(str, false);
}


