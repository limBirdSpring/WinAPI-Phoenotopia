#include "framework.h"
#include "CAttack.h"

#include "CRenderManager.h"
#include "CTimeManager.h"
#include "CEventManager.h"
#include "CCollider.h"
#include "CGameManager.h"

CAttack::CAttack()
{
	m_vecScale = Vector(30, 18);
	m_fTime = 0;
	m_layer = Layer::Missile;
	m_strName = L"����";
}

CAttack::~CAttack()
{
}

void CAttack::Init()
{
	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 1, m_vecScale.y - 1), Vector(0, 0));
	
}

void  CAttack::Update()
{
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
	Logger::Debug(L"�̻����� �浹ü�� �ε��� ������ϴ�.");
	
}

