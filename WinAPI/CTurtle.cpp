#include "framework.h"
#include "CTurtle.h"

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

CTurtle::CTurtle()
{

	m_vecScale = Vector(15, 8);
	m_layer = Layer::Monster;
	m_fSpeed = 10;
	m_damageHp = 3;
}

CTurtle::~CTurtle()
{
}

void CTurtle::Init()
{
	m_pImage = RESOURCE->LoadImg(L"Turtle", L"Image\\Turtle.png");

	m_pAnimator = new CAnimator;

	m_pAnimator->CreateAnimation(L"Turtle_Idle_Right", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.3f, 2, false);
	m_pAnimator->CreateAnimation(L"Turtle_Move_Right", m_pImage, Vector(300, 0), Vector(100, 100), Vector(150, 0), 0.3f, 3);
	m_pAnimator->CreateAnimation(L"Turtle_Idle_Left", m_pImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.3f, 2,false);
	m_pAnimator->CreateAnimation(L"Turtle_Move_Left", m_pImage, Vector(300, 150), Vector(100, 100), Vector(150, 0), 0.3f, 3);

	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 1, m_vecScale.y - 1), Vector(0, 11));

	m_pAnimator->Play(L"Turtle_Idle_Right", false);
	AddComponent(m_pAnimator);
	AddGravity(1);

	m_mapMonsterState.insert(make_pair(MonsterBehavior::Idle, new CMonsterIdle(this)));
	m_mapMonsterState.insert(make_pair(MonsterBehavior::Follow, new CMonsterFollow(this)));

	m_behavior = MonsterBehavior::Idle;
}

void CTurtle::Update()
{
	m_mapMonsterState.find(m_behavior)->second->Update();

	if (GAME->GetPlayerPos().x < m_vecPos.x + 80 && GAME->GetPlayerPos().x > m_vecPos.x - 80)
		m_behavior = MonsterBehavior::Follow;
	else
	{
		m_behavior = MonsterBehavior::Idle;
	}

	AnimatorUpdate();
}

void CTurtle::Render()
{

}

void CTurtle::Release()
{
}

void CTurtle::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"�÷��̾�")
	{
		Logger::Debug(L"���Ͱ� �÷��̾�� �浹����");
	}
	else if (pOtherCollider->GetObjName() == L"����")
	{
		Logger::Debug(L"���Ͱ� ���ݰ� �浹����");

	}
}

void CTurtle::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CTurtle::OnCollisionExit(CCollider* pOtherCollider)
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

void CTurtle::AnimatorUpdate()
{
	if (m_vecMoveDir.Length() > 0)
		m_vecLookDir = m_vecMoveDir;

	wstring str = L"Turtle";

	switch (m_behavior)
	{
	case MonsterBehavior::Follow: str += L"_Move";
		break;
	case MonsterBehavior::Damage: str += L"_Damage";
		break;
	default: str += L"_Idle";
	}

	if (m_vecLookDir.x > 0) str += L"_Right";
	else if (m_vecLookDir.x <= 0) str += L"_Left";

	m_pAnimator->Play(str, false);
}

