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
#include "CPlayer.h"


CCarol::CCarol(CPlayer* player)
{
	pPlayer = player;
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
	if (talk > 0)
	{
		if (BUTTONDOWN('X'))
		{
			talk++;
			Talk();
		}
	}

	if (m_choose != 0)
	{
		if (BUTTONDOWN(VK_UP))
		{
			m_choosing--;
		}
		if (BUTTONDOWN(VK_DOWN))
		{
			m_choosing++;
		}
		if (m_choosing <= 0)
			m_choosing = 1;
		else if (m_choosing > m_choose)
			m_choosing = m_choose;
	}
}

void CCarol::Render()
{
	if (m_strDialogue != L"")
	{
		if (m_strDialogue.length() > 20)
		{
			//RENDER->FillRect(m_vecPos.x - 130, m_vecPos.y - 100, m_vecPos.x + 70, m_vecPos.y - 50, Color(100, 100, 100, 255));
			RENDER->Image(m_pTalkBox, m_vecPos.x - 130, m_vecPos.y - 130, m_vecPos.x + 70, m_vecPos.y - 30);
			RENDER->Text(m_strDialogue, m_vecPos.x - 130 + 10, m_vecPos.y - 130, m_vecPos.x + 70 - 10, m_vecPos.y - 30);

			if (m_choose != 0)
			{
				RENDER->Image(m_pChoose, m_vecPos.x - 120, m_vecPos.y - 86 + (m_choosing * 8), m_vecPos.x - 120 + m_pChoose->GetWidth(), m_vecPos.y - 86 + (m_choosing * 8) + m_pChoose->GetHeight());
			}
		}
		else if (m_strDialogue.length() < 7)
		{
			RENDER->Image(m_pTalkBox, m_vecPos.x - 80, m_vecPos.y - 100, m_vecPos.x + 20, m_vecPos.y - 30);
			RENDER->Text(m_strDialogue, m_vecPos.x - 80 + 10, m_vecPos.y - 100, m_vecPos.x + 20 - 10, m_vecPos.y - 30);
		}
		else
		{
			RENDER->Image(m_pTalkBox, m_vecPos.x - 130, m_vecPos.y - 100, m_vecPos.x + 70, m_vecPos.y - 30);
			RENDER->Text(m_strDialogue, m_vecPos.x - 130 + 10, m_vecPos.y - 100, m_vecPos.x + 70 - 10, m_vecPos.y - 30);
		}
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
			CAMERA->ZoomInOut(2.3, 0.8);

			talk++;
			GAME->SetTalk(true);
			Talk();
			pOtherCollider->GetOwner()->SetPos(m_vecPos.x + 30, m_vecPos.y);
			pPlayer->m_vecMoveDir.x = -1;
			pPlayer->m_behavior = Behavior::Talk;
		}
	}
}

void CCarol::Talk()
{
	if (changeTalkTopic == 0)
	{
		switch (talk)
		{
		case 0:
			m_strDialogue = L"";
			break;
		case 1:
			m_strDialogue = L"오. 게일 안녕.";
			break;
		case 2:
			m_strDialogue = L"오늘은 매점에 신선한 페로 알이 들어왔다나봐.";
			break;
		default:
			CAMERA->ZoomInOut(2, 0.5);
			m_strDialogue = L"";
			GAME->SetTalk(false);
			changeTalkTopic++;
			talk = 0;
			break;
		}
	}
	else if (changeTalkTopic == 1)
	{
		switch (talk)
		{
		case 0:
			m_strDialogue = L"";
			break;
		case 1:
			m_strDialogue = L"그거 아니? Z키를 누르면 점프를 할 수 있어.";
			break;
		case 2:
			m_strDialogue = L"↓키를 누르면 앉을 수 있지.";
			break;
		case 3:
			m_strDialogue = L"앉은 상태에서 Z키를 누르면 하향 점프를 할 수 있어.";
			break;

		default:
			CAMERA->ZoomInOut(2, 0.5);
			m_strDialogue = L"";
			GAME->SetTalk(false);
			changeTalkTopic++;
			talk = 0;
			break;
		}
	}
	else if (changeTalkTopic == 2)
	{
		switch (talk)
		{
		case 0:
			m_strDialogue = L"";
			break;
		case 1:
			m_strDialogue = L"뭐? 더 높이 뛰는 방법은 없냐구?";
			break;
		case 2:
			m_strDialogue = L"Z키를 길게 눌러봐.";
			break;
		default:
			CAMERA->ZoomInOut(2, 0.5);
			m_strDialogue = L"";
			GAME->SetTalk(false);
			changeTalkTopic = 0;
			talk = 0;
			break;
		}
	}
}
