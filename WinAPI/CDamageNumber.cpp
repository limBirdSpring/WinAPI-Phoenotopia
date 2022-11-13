#include "framework.h"
#include "CDamageNumber.h"

CDamageNumber::CDamageNumber()
{
	m_layer = Layer::Things;
	m_pImage = nullptr;
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(10, 10);
	m_damage = 0;
	coolTime = 0;
}

CDamageNumber::~CDamageNumber()
{
}

void CDamageNumber::Init()
{
	m_pImage = RESOURCE->LoadImg(L"Number", L"Image\\Number.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"Number0", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.3, 1, false);
	m_pAnimator->CreateAnimation(L"Number1", m_pImage, Vector(150, 0), Vector(100, 100), Vector(150, 0), 0.3, 1, false);
	m_pAnimator->CreateAnimation(L"Number2", m_pImage, Vector(300, 0), Vector(100, 100), Vector(150, 0), 0.3, 1, false);
	m_pAnimator->CreateAnimation(L"Number3", m_pImage, Vector(450, 0), Vector(100, 100), Vector(150, 0), 0.3, 1, false);
	m_pAnimator->CreateAnimation(L"Number4", m_pImage, Vector(600, 0), Vector(100, 100), Vector(150, 0), 0.3, 1, false);
	m_pAnimator->CreateAnimation(L"Number5", m_pImage, Vector(750, 0), Vector(100, 100), Vector(150, 0), 0.3, 1, false);
	m_pAnimator->CreateAnimation(L"Number6", m_pImage, Vector(900, 0), Vector(100, 100), Vector(150, 0), 0.3, 1, false);
	m_pAnimator->CreateAnimation(L"Number7", m_pImage, Vector(1050, 0), Vector(100, 100), Vector(150, 0), 0.3, 1, false);
	m_pAnimator->CreateAnimation(L"Number8", m_pImage, Vector(1200, 0), Vector(100, 100), Vector(150, 0), 0.3, 1, false);
	m_pAnimator->CreateAnimation(L"Number9", m_pImage, Vector(1350, 0), Vector(100, 100), Vector(150, 0), 0.3, 1, false);


	AddComponent(m_pAnimator);

}

void CDamageNumber::Update()
{
	m_pAnimator->Play(L"Number"+to_wstring(m_damage));

	m_vecPos.y -= DT * 100;

	coolTime += DT;

	if (coolTime > 0.2)
		DELETEOBJECT(this);
}

void CDamageNumber::Render()
{
}

void CDamageNumber::Release()
{
}
