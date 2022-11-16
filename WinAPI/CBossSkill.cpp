#include "framework.h"
#include "CBossSkill.h"

CBossSkill::CBossSkill()
{
	m_layer = Layer::MonsterAttack;
	time = 0;
	coolTime = 0;
	idleTime = 0;
}

CBossSkill::~CBossSkill()
{
}

void CBossSkill::Init()
{
	
}

void CBossSkill::Update()
{

	if (coolTime != 0)
	{
		time += DT;

		if (time > idleTime)
			AddCollider(ColliderType::Rect, Vector(m_vecScale.x, m_vecScale.y), Vector(0, 0));

		if (coolTime+ idleTime <= time)
			DELETEOBJECT(this);
	}
}

void CBossSkill::Render()
{
}

void CBossSkill::Release()
{
}

void CBossSkill::OnCollisionEnter(CCollider* pOtherCollider)
{
	GAME->SetHp(-damage);

}

void CBossSkill::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CBossSkill::OnCollisionExit(CCollider* pOtherCollider)
{
}
