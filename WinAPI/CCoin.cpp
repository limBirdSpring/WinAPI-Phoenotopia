#include "framework.h"
#include "CCoin.h"
#include "CImage.h"

CCoin::CCoin()
{
	m_vecScale = Vector(10, 10);
	m_strName = L"코인";
	m_fSpeed = -100;
}

CCoin::~CCoin()
{
}

void CCoin::Init()
{
	m_pImage = RESOURCE->LoadImg(L"Coin", L"Image\\Coin.png");
	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 1, m_vecScale.y - 1), Vector(0, 0));
	AddGravity(1);
}

void CCoin::Update()
{
	if (this->GetGround())
	{
		m_vecPos.y--;
		SetGravity(m_fSpeed);
		m_fSpeed /= 2;
	}
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
