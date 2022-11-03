#include "framework.h"
#include "CAttack.h"

#include "CRenderManager.h"
#include "CTimeManager.h"
#include "CEventManager.h"
#include "CCollider.h"

CAttack::CAttack()
{
	m_vecScale = Vector(20, 20);
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


	m_fTime += DT;

	if (m_fTime > 2)
		DELETEOBJECT(this);
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
