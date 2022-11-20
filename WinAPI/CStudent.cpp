#include "framework.h"
#include "CStudent.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CResourceManager.h"
#include "CGameManager.h"
#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"
#include "CCameraManager.h"
#include "CPlayer.h"
#include "CTalkBox.h"


CStudent::CStudent(CPlayer* player)
{
	pPlayer = player;
	m_vecScale = Vector(18, 25);
	m_strDialogue = L"";
	talk = 0;
}

CStudent::~CStudent()
{
}

void CStudent::Init()
{

	m_pImage = RESOURCE->LoadImg(L"Student_Idle", L"Image\\Student_Idle.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"Student_Idle_Right", m_pImage, Vector(900, 0), Vector(100, 100), Vector(-150, 0), 0.15, 7);
	m_pAnimator->CreateAnimation(L"Student_Idle_Left", m_pImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.3, 2);

	m_pAnimator->Play(L"Student_Idle_Right");
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 0.1, m_vecScale.y - 0.1), Vector(0, 4));
}

void CStudent::Update()
{
	if (talk > 0)
	{
		if (BUTTONDOWN('X'))
		{
			CSound* pSe = RESOURCE->FindSound(L"Dialogue");
			SOUND->Play(pSe, 0.5);
			talk++;
			Talk();
		}
	}



}

void CStudent::Render()
{
	if (talk > 0)
	{
		pTalkBox->m_choose = &this->m_choose;
		pTalkBox->m_choosing = &this->m_choosing;
		pTalkBox->m_strDialogue = this->m_strDialogue;

	}
}

void CStudent::Release()
{
}

void CStudent::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		if (BUTTONDOWN('X'))
		{
			CAMERA->ZoomInOut(2.5, 1);

			talk++;
			GAME->SetTalk(true);
			Talk();
			pOtherCollider->GetOwner()->SetPos(m_vecPos.x + 30, m_vecPos.y);
			pPlayer->SetDir(Vector(-1, 0));
			pPlayer->m_behavior = Behavior::Talk;

			pTalkBox = new CTalkBox;
			pTalkBox->SetPos(this->GetPos());
			ADDOBJECT(pTalkBox);
		}
	}
}

void CStudent::Talk()
{
	
		switch (talk)
		{
		case 0:
			m_strDialogue = L"";
			break;
		case 1:
			m_strDialogue = L"게일 언니 오랜만이야!";
			break;
		case 2:
			m_strDialogue = L"연습하러 온거야?";
			break;
		case 3:
			m_strDialogue = L"그나저나 사부님 진짜 나빴어.";
			break;
		case 4:
			m_strDialogue = L"이 동작만 100번을 시키다니!";
			break;
		default:
			CAMERA->ZoomInOut(2, 1.5);
			m_strDialogue = L"";
			GAME->SetTalk(false);
			talk = 0;
			DELETEOBJECT(pTalkBox);
			break;
		}


}
