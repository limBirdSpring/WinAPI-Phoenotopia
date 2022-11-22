#include "framework.h"
#include "CTreasure.h"

#include "CCollider.h"
#include "CGravity.h"
#include "CImage.h"
#include "CItem.h"
#include "CAnimator.h"
#include "CCoin.h"

CTreasure::CTreasure()
{
	m_vecScale = Vector(15, 15);
	m_strName = L"보물";
	m_hp = 3;
}

CTreasure::~CTreasure()
{
}

void CTreasure::Init()
{
	m_pImage = RESOURCE->LoadImg(L"Treasure", L"Image\\Treasure.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"Treasure", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.3, 1, false);


	m_pAnimator->Play(L"Treasure");
	AddComponent(m_pAnimator);


	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 1, m_vecScale.y - 1), Vector(0, 7));
	AddGravity(1);
}

void CTreasure::Update()
{
	if (m_hp <= 0)
	{

		CCoin* pCoin = new CCoin;
		pCoin->SetPrice(85);
		pCoin->SetPos(this->GetPos());
		pCoin->SetDir(Vector(-1,0));
		pCoin->SetSpeed(20);
		ADDOBJECT(pCoin);

		CCoin* coin = new CCoin;
		coin->SetPos(this->GetPos());
		coin->SetDir(Vector(0,0));
		coin->SetPrice(50);
		pCoin->SetSpeed(25);
		ADDOBJECT(coin);

		CCoin* coin2 = new CCoin;
		coin2->SetPos(this->GetPos());
		coin2->SetDir(Vector(1, 0));
		coin2->SetPrice(5);
		pCoin->SetSpeed(1);
		ADDOBJECT(coin2);
		CCoin* coin3 = new CCoin;
		coin3->SetPos(this->GetPos());
		coin3->SetDir(Vector(-1, 0));
		coin3->SetPrice(10);
		pCoin->SetSpeed(15);
		ADDOBJECT(coin3);
		CCoin* coin4 = new CCoin;
		coin4->SetPos(this->GetPos());
		coin4->SetDir(Vector(0, 0));
		coin4->SetPrice(10);
		ADDOBJECT(coin4);


		pSe = RESOURCE->FindSound(L"Treasure");
		SOUND->Play(pSe);
		DELETEOBJECT(this);
	}

}

void CTreasure::Render()
{
}

void CTreasure::Release()
{
}

void CTreasure::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"공격")
	{
		m_hp = 0;
	}
}

void CTreasure::OnCollisionStay(CCollider* pOtherCollider)
{

}

void CTreasure::OnCollisionExit(CCollider* pOtherCollider)
{

}
