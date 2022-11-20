#include "framework.h"
#include "CCritical.h"

#include "CRenderManager.h"
#include "CTimeManager.h"
#include "CEventManager.h"
#include "CCollider.h"
#include "CGameManager.h"
#include "CDamageNumber.h"

CCritical::CCritical()
{
	m_vecScale = Vector(60, 60);
	m_fTime = 0;
	m_layer = Layer::Missile;
	m_strName = L"공격";
}

CCritical::~CCritical()
{
}

void CCritical::Init()
{

}

void  CCritical::Update()
{
	if (m_fTime > 0.5)
	{
		RemoveCollider();
		AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 1, m_vecScale.y - 1), Vector(0, 0));
	}

	Vector pos = GAME->GetPlayerPos();

	if (GAME->GetPlayerDir().x == -1)
		this->SetPos(pos.x, pos.y);
	else if (GAME->GetPlayerDir().x == 1)
		this->SetPos(pos.x, pos.y);

	m_fTime += DT;

	if (m_fTime > 1)
	{
		DELETEOBJECT(this);
	}
}

void  CCritical::Render()
{

}

void  CCritical::Release()
{
}

void  CCritical::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetOwner()->GetLayer() == Layer::Monster || pOtherCollider->GetOwner()->GetLayer() == Layer::FlyingMonster || pOtherCollider->GetOwner()->GetLayer() == Layer::Boss
		|| pOtherCollider->GetObjName() == L"박스")
	{
		if (pOtherCollider->GetObjName() == L"박스")
		{
			pSe = RESOURCE->FindSound(L"BoxDamage");
			SOUND->Play(pSe);
		}

		pOtherCollider->GetOwner()->SetHp(-9);

		CDamageNumber* pNum = new CDamageNumber;
		if (pOtherCollider->GetObjName() == L"Slug")
			pNum->m_damage = 0;
		else
			pNum->m_damage = 9;
		pNum->SetPos(pOtherCollider->GetPos());
		ADDOBJECT(pNum);
		
	}
	DELETEOBJECT(this);
}

