#include "framework.h"
#include "CCarol.h"

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


CCarol::CCarol()
{
	m_vecScale = Vector(18, 32);
	m_strDialogue = L"";
	talk = 0;
}

CCarol::~CCarol()
{
}

void CCarol::Init()
{
	
	m_pImage = RESOURCE->LoadImg(L"Carol_Idle", L"Image\\Carol_Idle.png");
	
	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"Carol_Idle_Right", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.5, 4);
	m_pAnimator->CreateAnimation(L"Carol_Idle_Left", m_pImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.5, 4);
	
	m_pAnimator->Play(L"Carol_Idle_Right");
	AddComponent(m_pAnimator);
	
	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 0.1, m_vecScale.y - 0.1), Vector(0, 4));
}

void CCarol::Update()
{
	if (GAME->GetTalk())
	{
		if (BUTTONDOWN('X'))
		{
			talk++;
			Talk();
		}
	}
}

void CCarol::Render()
{
	if (m_strDialogue != L"")
	{
		//RENDER->FillRect(m_vecPos.x - 130, m_vecPos.y - 100, m_vecPos.x + 70, m_vecPos.y - 50, Color(100, 100, 100, 255));
		RENDER->Image(m_pTalkBox, m_vecPos.x - 130, m_vecPos.y - 130, m_vecPos.x + 70, m_vecPos.y - 30);
		RENDER->Text(m_strDialogue, m_vecPos.x - 130 + 10, m_vecPos.y - 130, m_vecPos.x + 70 - 10, m_vecPos.y - 30);
		
	}
}

void CCarol::Release()
{
}

void CCarol::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		if (BUTTONDOWN('X'))
		{
			CAMERA->ZoomInOut(3, 1);

			talk++;
			GAME->SetTalk(true);
			Talk();
			pOtherCollider->GetOwner()->SetPos(m_vecPos.x + 30, m_vecPos.y);
			pOtherCollider->GetOwner()->SetDir(Vector(-1, 0));
		}
	}
}

void CCarol::Talk()
{
	switch (talk)
	{
	case 0:
		m_strDialogue = L"";
		break;
	case 1:
		m_strDialogue = L"뭐? 딸기케이크?";
		break;
	case 2:
		m_strDialogue = L"그건 벌써 다 팔렸는데?";
		break;
	case 3:
		m_strDialogue = L"대신 신선한 계란이 들어왔어.";
		break;
	case 4:
		m_strDialogue = L"";
		break;
	case 5:
		m_strDialogue = L"딸기케이크 말고도 먹을 만한게 많으니 얼마든지 골라보렴";
		break;
	default :
		CAMERA->ZoomInOut(2, 1.5);
		m_strDialogue = L"";
		GAME->SetTalk(false);
		talk = 0;
		break;
	}
}
