#include "framework.h"
#include "CCoin.h"
#include "CImage.h"

CCoin::CCoin()
{
	m_vecScale = Vector(10, 10);
	m_strName = L"코인";
	m_fSpeed = 100;
}

CCoin::~CCoin()
{
}

void CCoin::Init()
{
	if (rand()%2 ==0)
		m_pImage = RESOURCE->LoadImg(L"Coin", L"Image\\Coin.png");
	else
		m_pImage = RESOURCE->LoadImg(L"Coin2", L"Image\\Coin2.png");
	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 1, m_vecScale.y - 1), Vector(0, 0));
	AddGravity(-100);
}

void CCoin::Update()
{
	if (this->GetGround() ==0 && GetGravity() > 10)
		jumpSpeed = -GetGravity();
	
	if (this->GetGround()&& jumpSpeed < -50)
	{
		m_vecPos.y--;
		SetGravity(jumpSpeed /2);
	}

	m_vecPos.x += m_vecMoveDir.x * DT * m_fSpeed;

	if (m_fSpeed < 1)
		m_fSpeed = 0;
	else
		m_fSpeed -= m_fSpeed * 0.8 * DT;//마찰계수만큼 속도 줄이기


}

void CCoin::Render()
{
	RENDER->Image(m_pImage, m_vecPos.x - m_pImage->GetWidth()*0.5, m_vecPos.y - m_pImage->GetHeight()*0.5, m_vecPos.x + m_pImage->GetWidth()*0.5, m_vecPos.y + m_pImage->GetHeight()*0.5);
}

void CCoin::Release()
{
}

void CCoin::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		GAME->SetGold(price);
		DELETEOBJECT(this);
	}
}

void CCoin::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CCoin::OnCollisionExit(CCollider* pOtherCollider)
{
}
