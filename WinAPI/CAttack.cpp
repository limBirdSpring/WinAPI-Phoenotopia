#include "framework.h"
#include "CAttack.h"

#include "CRenderManager.h"
#include "CTimeManager.h"
#include "CEventManager.h"
#include "CCollider.h"
#include "CGameManager.h"

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
		m_vecScale.x = 30;
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
		GAME->SetAttack(false);
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
	Logger::Debug(L"미사일이 충돌체와 부딪혀 사라집니다.");
	
}

