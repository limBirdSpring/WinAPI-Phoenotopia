#include "framework.h"
#include "CAttack2.h"

#include "CRenderManager.h"
#include "CTimeManager.h"
#include "CEventManager.h"
#include "CCollider.h"
#include "CGameManager.h"

//공중공격

CAttack2::CAttack2()
{
	m_vecScale = Vector(30, 30);
	m_fTime = 0;
	m_layer = Layer::Missile;
	m_strName = L"공격";
}

CAttack2::~CAttack2()
{
}

void CAttack2::Init()
{
	

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
		GAME->SetAttack(false);
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
	Logger::Debug(L"미사일이 충돌체와 부딪혀 사라집니다.");

}

