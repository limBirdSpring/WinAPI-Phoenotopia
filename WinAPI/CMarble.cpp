#include "framework.h"
#include "CMarble.h"

#include "CCollider.h"
#include "CGravity.h"
#include "CImage.h"
#include "CItem.h"
#include "CAnimator.h"

CMarble::CMarble()
{
	m_vecScale = Vector(15, 15);
	isMarbleOn = true;
	m_layer = Layer::Things;
}

CMarble::~CMarble()
{
	
}

void CMarble::Init()
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

void CMarble::Update()
{
	
	if (isMarbleOn)
	{
		m_pAnimator->Play(L"Marble_"+dir+L"_On");
	}
	else
	{
		m_pAnimator->Play(L"Marble_" + dir + L"_Off");
	}

}

void CMarble::Render()
{
}

void CMarble::Release()
{
}

void CMarble::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"АјАн")
	{
		isMarbleOn = !isMarbleOn;
		pSe = RESOURCE->FindSound(L"PillarDoor");
		SOUND->Play(pSe);
	}
}

void CMarble::OnCollisionStay(CCollider* pOtherCollider)
{

}

void CMarble::OnCollisionExit(CCollider* pOtherCollider)
{

}
