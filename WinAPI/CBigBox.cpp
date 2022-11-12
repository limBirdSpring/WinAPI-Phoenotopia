#include "framework.h"
#include "CBigBox.h"

#include "CCollider.h"
#include "CGravity.h"
#include "CImage.h"
#include "CAnimator.h"

CBigBox::CBigBox()
{
	m_vecScale = Vector(15, 15);
	m_strName = L"박스";
	m_hp = 12;
}

CBigBox::~CBigBox()
{
}

void CBigBox::Init()
{
	m_pImage = RESOURCE->LoadImg(L"BigBox", L"Image\"BigBox.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"BigBox", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.3, 1, false);
	m_pAnimator->CreateAnimation(L"BigBox2", m_pImage, Vector(150, 0), Vector(100, 100), Vector(150, 0), 0.3, 1, false);
	m_pAnimator->CreateAnimation(L"BigBox3", m_pImage, Vector(300, 0), Vector(100, 100), Vector(150, 0), 0.3, 1, false);
	m_pAnimator->CreateAnimation(L"BigBox4", m_pImage, Vector(450, 0), Vector(100, 100), Vector(150, 0), 0.3, 1, false);

	m_pAnimator->Play(L"BigBox");
	AddComponent(m_pAnimator);


	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 1, m_vecScale.y - 1), Vector(0, 0));
	AddGravity(1);
}

void CBigBox::Update()
{
	if (m_hp < 0)
	{
		DELETEOBJECT(this);
	}
	else if (m_hp <=3)
	{
		m_pAnimator->Play(L"BigBox4");
	}
	else if (m_hp <= 6)
	{
		m_pAnimator->Play(L"BigBox3");
	}
	else if (m_hp <= 9)
	{
		m_pAnimator->Play(L"BigBox2");
	}
	else
	{
		m_pAnimator->Play(L"BigBox");
	}

}

void CBigBox::Render()
{
}

void CBigBox::Release()
{
}

void CBigBox::OnCollisionEnter(CCollider* pOtherCollider)
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

		else if (GAME->GetPlayerDir().x == -1)
			m_vecPos.x--;
		else
			m_vecPos.x++;




	}
}

void CBigBox::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CBigBox::OnCollisionExit(CCollider* pOtherCollider)
{
	if (isGroundPlus)
	{
		int ground = pOtherCollider->GetOwner()->GetGround();
		pOtherCollider->GetOwner()->SetGround(--ground);
		isGroundPlus = false;
	}
}
