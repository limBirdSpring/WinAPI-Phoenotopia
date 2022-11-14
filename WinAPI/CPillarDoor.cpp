#include "framework.h"
#include "CPillarDoor.h"
#include "CMarble.h"
#include "CImage.h"
#include "CStatue"

CPillarDoor::CPillarDoor()
{
	m_layer = Layer::Door;
	m_vecScale = Vector(14, 80);
	m_fSpeed = 100;
}


CPillarDoor::~CPillarDoor()
{
}

void CPillarDoor::Init()
{
	
	m_pImage = RESOURCE->LoadImg(L"PillarDoor", L"Image\\PillarDoor.png");
	isSaveY = false;

	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 1, m_vecScale.y - 1), Vector(0, 0));
}

void CPillarDoor::Update()
{
	if (!isSaveY && m_vecPos.y > 0)
	{
		closeY = m_vecPos.y;
		openY = m_vecPos.y - m_pImage->GetHeight();
		isSaveY = true;
	}

	if (pMarble != nullptr)
	{
		if (pMarble->isMarbleOn)
		{
			if (m_vecPos.y < closeY)
				this->m_vecPos.y += DT * m_fSpeed;
		}
		else
		{
			if (m_vecPos.y > openY)
				this->m_vecPos.y -= DT * m_fSpeed;
		}
	}
	else if (pStatue != nullptr)
	{
		if (pStatue->isPillarOn)
		{
			if (m_vecPos.y < closeY)
				this->m_vecPos.y += DT * m_fSpeed;
		}
		else
		{
			if (m_vecPos.y > openY)
				this->m_vecPos.y -= DT * m_fSpeed;
		}
	}
}

void CPillarDoor::Render()
{
	RENDER->Image(m_pImage, m_vecPos.x - m_pImage->GetWidth() * 0.5, m_vecPos.y - m_pImage->GetHeight() * 0.5, m_vecPos.x + m_pImage->GetWidth() *0.5, m_vecPos.y + m_pImage->GetHeight() * 0.5);
}

void CPillarDoor::Release()
{
}

void CPillarDoor::OnCollisionEnter(CCollider* pOtherCollider)
{
}

void CPillarDoor::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CPillarDoor::OnCollisionExit(CCollider* pOtherCollider)
{
}
