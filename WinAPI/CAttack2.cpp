#include "framework.h"
#include "CAttack2.h"

#include "CRenderManager.h"
#include "CTimeManager.h"
#include "CEventManager.h"
#include "CCollider.h"
#include "CGameManager.h"
#include "CDamageNumber.h"

//���߰���

CAttack2::CAttack2()
{
	m_vecScale = Vector(40, 40);
	m_fTime = 0;
	m_layer = Layer::Missile;
	m_strName = L"����";
}

CAttack2::~CAttack2()
{
}

void CAttack2::Init()
{
	pSe = RESOURCE->FindSound(L"Attack2");
	SOUND->Play(pSe);

}

void  CAttack2::Update()
{
	if (m_fTime > 0.3)
	{
		RemoveCollider();
		AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 1, m_vecScale.y - 1), Vector(0, 0));
	}

	Vector pos = GAME->GetPlayerPos();

	if (GAME->GetPlayerDir().x == -1)
		this->SetPos(pos.x - 7, pos.y + 5);
	else if (GAME->GetPlayerDir().x == 1)
		this->SetPos(pos.x + 7, pos.y + 5);


	m_fTime += DT;

	if (m_fTime > 0.66)
	{
		DELETEOBJECT(this);
	}
}

void  CAttack2::Render()
{

}

void  CAttack2::Release()
{
}

void  CAttack2::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetOwner()->GetLayer() == Layer::Monster || pOtherCollider->GetOwner()->GetLayer() == Layer::FlyingMonster || pOtherCollider->GetOwner()->GetLayer() == Layer::Boss
		|| pOtherCollider->GetObjName() == L"�ڽ�")
	{
		pOtherCollider->GetOwner()->SetHp(-5);
		CDamageNumber* pNum = new CDamageNumber;
		if (pOtherCollider->GetObjName() == L"Slug")
			pNum->m_damage = 0;
		else
			pNum->m_damage = 5;
		pNum->SetPos(pOtherCollider->GetPos());
		ADDOBJECT(pNum);

		
	}
	DELETEOBJECT(this);
}

