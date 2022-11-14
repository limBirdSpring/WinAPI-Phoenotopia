#include "framework.h"
#include "CStatue.h"

#include "CCollider.h"
#include "CGravity.h"
#include "CImage.h"
#include "CItem.h"
#include "CAnimator.h"

CStatue::CStatue()
{
	m_vecScale = Vector(15, 15);
	isStatueOn = true;
	m_layer = Layer::Things;
}

CStatue::~CStatue()
{

}

void CStatue::Init()
{
	m_pImage = RESOURCE->LoadImg(L"Marble", L"Image\\Marble.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"Marble_Left_On", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.3, 1, false);
	m_pAnimator->CreateAnimation(L"Marble_Left_Off", m_pImage, Vector(150, 0), Vector(100, 100), Vector(150, 0), 0.3, 1, false);
	m_pAnimator->CreateAnimation(L"Marble_Up_On", m_pImage, Vector(300, 0), Vector(100, 100), Vector(150, 0), 0.3, 1, false);
	m_pAnimator->CreateAnimation(L"Marble_Up_Off", m_pImage, Vector(450, 0), Vector(100, 100), Vector(150, 0), 0.3, 1, false);
	m_pAnimator->CreateAnimation(L"Marble_Right_On", m_pImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.3, 1, false);
	m_pAnimator->CreateAnimation(L"Marble_Right_Off", m_pImage, Vector(150, 150), Vector(100, 100), Vector(150, 0), 0.3, 1, false);


	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 1, m_vecScale.y - 1), Vector(0, 0));
}

void CStatue::Update()
{

	if (isStatueOn)
	{
		m_pAnimator->Play(L"Marble_" + dir + L"_On");
	}
	else
	{
		m_pAnimator->Play(L"Marble_" + dir + L"_Off");
	}

}

void CStatue::Render()
{
}

void CStatue::Release()
{
}

void CStatue::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"АјАн")
	{
		isStatueOn = !isStatueOn;
	}
}

void CStatue::OnCollisionStay(CCollider* pOtherCollider)
{

}

void CStatue::OnCollisionExit(CCollider* pOtherCollider)
{

}
