#include "framework.h"
#include "CAttack.h"

#include "CRenderManager.h"
#include "CTimeManager.h"
#include "CEventManager.h"
#include "CCollider.h"
#include "CGameManager.h"
#include "CDamageNumber.h"

CAttack::CAttack()
{
	m_vecScale = Vector(2, 18);
	m_fTime = 0;
	m_layer = Layer::Missile;
	m_strName = L"공격";
}

CAttack::~CAttack()
{
}

void CAttack::Init()
{
}

void  CAttack::Update()
{
	if (m_fTime > 0.2)
	{
		m_vecScale.x = 40;
		RemoveCollider();
		AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 1, m_vecScale.y - 1), Vector(0, 0));
	}

	Vector pos = GAME->GetPlayerPos();

	if (GAME->GetPlayerDir().x == -1)
		this->SetPos(pos.x - 10, pos.y + 7);
	else if (GAME->GetPlayerDir().x == 1)
		this->SetPos(pos.x + 10, pos.y + 7);

	m_fTime += DT;

	if (m_fTime > 0.5)
	{
		DELETEOBJECT(this);
	}
}

void  CAttack::Render()
{

}

void  CAttack::Release()
{
}

void  CAttack::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetOwner()->GetLayer() == Layer::Monster || pOtherCollider->GetOwner()->GetLayer() == Layer::FlyingMonster || pOtherCollider->GetObjName() == L"박스")
	{
		pOtherCollider->GetOwner()->SetHp(-3);
		CDamageNumber* pNum = new CDamageNumber;
		if (pOtherCollider->GetObjName() == L"Slug")
			pNum->m_damage = 0;
		else
			pNum->m_damage = 3;
		pNum->SetPos(pOtherCollider->GetPos());
		ADDOBJECT(pNum);

		DELETEOBJECT(this);
	}
}

