#include "framework.h"
#include "CBox.h"
#include "CCollider.h"
#include "CGravity.h"
#include "CImage.h"

CBox::CBox()
{
	m_vecScale = Vector(15, 15);
	m_strName = L"아이템";
}

CBox::~CBox()
{
}

void CBox::Init()
{
	m_pImage = RESOURCE->LoadImg(L"Box", L"Image\\Box.png");
	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 1, m_vecScale.y - 1), Vector(0, 0));
	AddGravity(1);
}

void CBox::Update()
{
}

void CBox::Render()
{
	RENDER->Image(m_pImage, m_vecPos.x - m_pImage->GetWidth()*0.5, m_vecPos.y - m_pImage->GetHeight() * 0.5, m_vecPos.x + m_pImage->GetWidth() * 0.5, m_vecPos.y + m_pImage->GetHeight()*0.5);
}

void CBox::Release()
{
}

void CBox::OnCollisionEnter(CCollider* pOtherCollider)
{
	//TODO: 박스 위에 올라갈 수 있게 하기 추가

	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		if (GAME->GetPlayerDir().x==-1) 
			m_vecPos.x--;
		else
			m_vecPos.x++;

	}
}

void CBox::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CBox::OnCollisionExit(CCollider* pOtherCollider)
{
}
