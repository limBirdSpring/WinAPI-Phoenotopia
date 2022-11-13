#include "framework.h"
#include "CBox.h"
#include "CCollider.h"
#include "CGravity.h"
#include "CImage.h"
#include "CPlayer.h"

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
	

	if (pOtherCollider->GetObjName() == L"플레이어")
	{

		if (0 < pOtherCollider->GetOwner()->GetGravity() &&
			((pOtherCollider->GetOwner()->GetColliderPos().y) + (pOtherCollider->GetOwner()->GetScale().y * 0.5) < this->GetPos().y))
		{
			pOtherCollider->GetOwner()->SetPos(pOtherCollider->GetOwner()->GetPos().x,
				this->GetPos().y - this->GetScale().y * 0.5 - ((pOtherCollider->GetOwner()->GetColliderPos().y - pOtherCollider->GetOwner()->GetPos().y) + pOtherCollider->GetOwner()->GetScale().y * 0.5) + 1);

			int ground = pOtherCollider->GetOwner()->GetGround();
			pOtherCollider->GetOwner()->SetGround(++ground);

			isGroundPlus = true;
		}
		else if (BUTTONSTAY('A'))
		{
			if (GAME->GetPlayerDir().x == -1)
			{
				pOtherCollider->GetOwner()->SetSpeed(30);
				m_vecPos.x--;
			}
			else
			{
				pOtherCollider->GetOwner()->SetSpeed(30);
				m_vecPos.x++;
			}
		}


	}
}

void CBox::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CBox::OnCollisionExit(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		if (isGroundPlus)
		{
			int ground = pOtherCollider->GetOwner()->GetGround();
			pOtherCollider->GetOwner()->SetGround(--ground);
			isGroundPlus = false;
		}
	}
}
