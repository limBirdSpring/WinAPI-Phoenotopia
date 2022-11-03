#include "framework.h"
#include "CPlayer.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CResourceManager.h"
#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"

#include "CMissile.h"

CPlayer::CPlayer()
{
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(20, 34);
	m_layer = Layer::Player;
	m_strName = L"플레이어";
	m_fSpeed = 100;

	m_pIdleImage = nullptr;
	m_pMoveImage = nullptr;
	m_pRunImage = nullptr;
	m_pJumpImage = nullptr;
	m_pDownImage = nullptr;

	m_vecMoveDir = Vector(0, 0);
	m_vecLookDir = Vector(0, -1);
	m_behavior = Behavior::Idle;
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
	m_pIdleImage = RESOURCE->LoadImg(L"Gail_Standing", L"Image\\Gail_Standing.png");
	m_pMoveImage = RESOURCE->LoadImg(L"Gail_Walking", L"Image\\Gail_Walking.png");
	m_pRunImage = RESOURCE->LoadImg(L"Gail_Run", L"Image\\Gail_Run.png");
	m_pJumpImage = RESOURCE->LoadImg(L"Gail_Jump", L"Image\\Gail_Jump.png");
	m_pDownImage = RESOURCE->LoadImg(L"Gail_Down", L"Image\\Gail_Down.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"Gail_Standing_Right", m_pIdleImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.2f, 6);
	m_pAnimator->CreateAnimation(L"Gail_Standing_Left", m_pIdleImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.2f, 6);
	m_pAnimator->CreateAnimation(L"Gail_Walking_Right", m_pMoveImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.1f, 8);
	m_pAnimator->CreateAnimation(L"Gail_Walking_Left", m_pMoveImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.1f, 8);
	m_pAnimator->CreateAnimation(L"Gail_Run_Right", m_pRunImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.1f, 6);
	m_pAnimator->CreateAnimation(L"Gail_Run_Left", m_pRunImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.1f, 6);
	m_pAnimator->CreateAnimation(L"Gail_Jump_Right", m_pJumpImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.1f, 13, false);
	m_pAnimator->CreateAnimation(L"Gail_Jump_Left", m_pJumpImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.1f, 13, false);
	m_pAnimator->CreateAnimation(L"Gail_Fall_Right", m_pJumpImage, Vector(750, 0), Vector(100, 100), Vector(150, 0), 0.1f, 8);
	m_pAnimator->CreateAnimation(L"Gail_Fall_Left", m_pJumpImage, Vector(750, 150), Vector(100, 100), Vector(150, 0), 0.1f, 8);
	m_pAnimator->CreateAnimation(L"Gail_Down_Right", m_pDownImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.15f, 4, false);
	m_pAnimator->CreateAnimation(L"Gail_Down_Left", m_pDownImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.15f, 4, false);

	m_pAnimator->Play(L"Gail_Standing_Right", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 1, m_vecScale.y - 1), Vector(0, 0));
	AddGravity(1);
}

void CPlayer::Update()
{

	if (!GetGround())
	{
		if (GetGravity() > 100)
			m_behavior = Behavior::Fall;
		else
			m_behavior = Behavior::Jump;
	}
	//앉기
	else if (BUTTONSTAY(VK_DOWN) && GetGround())
	{
		m_behavior = Behavior::Down;
	}

	else
	{
		m_behavior = Behavior::Idle;
	}

	//점프
	if (BUTTONSTAY(VK_DOWN) && BUTTONDOWN('X') && GetPlatform() != 0)//하향점프
	{
		m_behavior = Behavior::Jump;
		this->SetGround(0);
		this->SetPlatform(0);
		this->SetGravity(1);
	}
	else if (BUTTONDOWN('X') && GetGround())
	{
		m_behavior = Behavior::Jump;
		m_vecPos.y--;
		SetGravity(-300);
	}



	//걷기
	if (BUTTONSTAY(VK_LEFT))
	{
		m_vecPos.x -= m_fSpeed * DT;
		if (GetGround())
			m_behavior = Behavior::Walk;
		m_vecMoveDir.x = -1;
	}
	else if (BUTTONSTAY(VK_RIGHT))
	{
		m_vecPos.x += m_fSpeed * DT;
		if (GetGround())
			m_behavior = Behavior::Walk;
		m_vecMoveDir.x = +1;
	}

	//뛰기
	if (BUTTONSTAY(VK_LEFT) && BUTTONSTAY(VK_SHIFT) && GetGround())
	{
		m_vecPos.x -= (m_fSpeed + 50) * DT;
		m_behavior = Behavior::Run;
		m_vecMoveDir.x = -1;
	}
	else if (BUTTONSTAY(VK_RIGHT) && BUTTONSTAY(VK_SHIFT) && GetGround())
	{
		m_vecPos.x += (m_fSpeed + 50) * DT;
		m_behavior = Behavior::Run;
		m_vecMoveDir.x = +1;
	}



	//if (BUTTONSTAY(VK_UP))
	//{
	//	m_vecPos.y -= m_fSpeed * DT;
	//	m_bIsMove = true;
	//	m_vecMoveDir.y = +1;
	//}
	//else if (BUTTONSTAY(VK_DOWN))
	//{
	//	m_vecPos.y += m_fSpeed * DT;
	//	m_bIsMove = true;
	//	m_vecMoveDir.y = -1;
	//}
	//else
	//{
	//	m_vecMoveDir.y = 0;
	//}





	if (BUTTONDOWN(VK_SPACE))
	{
		CreateMissile();
	}

	AnimatorUpdate();
}

void CPlayer::Render()
{
}

void CPlayer::Release()
{
}

void CPlayer::AnimatorUpdate()
{
	if (m_vecMoveDir.Length() > 0)
		m_vecLookDir = m_vecMoveDir;

	wstring str = L"Gail";

	switch (m_behavior)
	{
	case Behavior::Walk: str += L"_Walking";
		break;
	case Behavior::Run: str += L"_Run";
		break;
	case Behavior::Jump: str += L"_Jump";
		break;
	case Behavior::Fall: str += L"_Fall";
		break;
	case Behavior::Down: str += L"_Down";
		break;
	default: str += L"_Standing";
	}


	if (m_vecLookDir.x > 0) str += L"_Right";
	else if (m_vecLookDir.x <= 0) str += L"_Left";

	m_pAnimator->Play(str, false);
}

void CPlayer::CreateMissile()
{
	Logger::Debug(L"미사일 생성");

	CMissile* pMissile = new CMissile();
	pMissile->SetPos(m_vecPos);
	pMissile->SetDir(Vector(1, 0));
	ADDOBJECT(pMissile);

	CMissile* pMissile1 = new CMissile();
	pMissile1->SetPos(m_vecPos);
	pMissile1->SetDir(Vector(1, -1));
	ADDOBJECT(pMissile1);

	CMissile* pMissile2 = new CMissile();
	pMissile2->SetPos(m_vecPos);
	pMissile2->SetDir(Vector(1, 1));
	ADDOBJECT(pMissile2);

	CMissile* pMissile3 = new CMissile();
	pMissile3->SetPos(m_vecPos);
	pMissile3->SetDir(Vector(3, 1));
	ADDOBJECT(pMissile3);

	CMissile* pMissile4 = new CMissile();
	pMissile4->SetPos(m_vecPos);
	pMissile4->SetDir(Vector(3, -1));
	ADDOBJECT(pMissile4);
}

void CPlayer::OnCollisionEnter(CCollider* pOtherCollider)
{
}

void CPlayer::OnCollisionStay(CCollider* pOtherCollider)
{


}

void CPlayer::OnCollisionExit(CCollider* pOtherCollider)
{

}
