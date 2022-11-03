#include "framework.h"
#include "CCritical.h"

#include "CRenderManager.h"
#include "CTimeManager.h"
#include "CEventManager.h"
#include "CCollider.h"
#include "CGameManager.h"

CCritical::CCritical()
{
	m_vecScale = Vector(50, 50);
	m_fTime = 0;
	m_layer = Layer::Missile;
	m_strName = L"공격";
}

CCritical::~CCritical()
{
}

void CCritical::Init()
{
	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 1, m_vecScale.y - 1), Vector(0, 0));

}

void  CCritical::Update()
{
	Vector pos = GAME->GetPlayerPos();

	if (GAME->GetPlayerDir().x == -1)
		this->SetPos(pos.x, pos.y);
	else if (GAME->GetPlayerDir().x == 1)
		this->SetPos(pos.x, pos.y);

	m_fTime += DT;

	if (m_fTime > 1)
	{
		GAME->SetAttack(false);
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
	Logger::Debug(L"미사일이 충돌체와 부딪혀 사라집니다.");

}

