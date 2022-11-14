#include "framework.h"
#include "CNana.h"

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


CNana::CNana(CPlayer* player)
{
	pPlayer = player;
	m_vecScale = Vector(22, 32);
	m_strDialogue = L"";
	talk = 0;
}

CNana::~CNana()
{
}

void CNana::Init()
{

	m_pImage = RESOURCE->LoadImg(L"Nana_Idle", L"Image\\Nana_Idle.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"Nana_Idle_Right", m_pImage, Vector(300, 0), Vector(100, 100), Vector(150, 0), 0.2, 7);
	m_pAnimator->CreateAnimation(L"Nana_Talk_Right", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.5, 2);

	m_pAnimator->Play(L"Nana_Idle_Right");
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 0.1, m_vecScale.y - 0.1), Vector(0, 4));
}

void CNana::Update()
{

	if (talk == 0)
	{
		m_pAnimator->Play(L"Nana_Idle_Right");
	}
	else
	{
		m_pAnimator->Play(L"Nana_Talk_Right");
	}


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

void CNana::Render()
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

void CNana::Release()
{
}

void CNana::OnCollisionStay(CCollider* pOtherCollider)
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
			pPlayer->SetDir(Vector( - 1, 0));
			pPlayer->m_behavior = Behavior::Talk;
		}
	}
}

void CNana::Talk()
{
	if (changeTalkTopic == 0)
	{
		switch (talk)
		{
		case 0:
			m_strDialogue = L"";
			break;
		case 1:
			m_strDialogue = L"오, 게일왔구나. 오늘은 마침 날씨가 맑은데, 어디 놀러가니?";
			break;
		case 2:
			m_strDialogue = L"아 맞다. 그러고보니 알려줄것이 있단다.";
			break;
		case 3:
			m_strDialogue = L"너 혹시 상자 미는 법에 대해 아니?";
			break;
		case 4:
			m_strDialogue = L"A키를 누르고 상자에 접근하면 된단다. 한번 해보렴.";
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
			m_strDialogue = L"뭐? 큰 상자는 안 밀린다고? 허허..";
			break;
		case 2:
			m_strDialogue = L"큰 상자는 아직 너에게 너무 무거운가보구나.";
			break;
		case 3:
			m_strDialogue = L"대신 큰 상자는 공격을 하여 부술 수 있단다.";
			break;
		case 4:
			m_strDialogue = L"운이 좋으면 아이템이 들어있기도 하지.";
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
			m_strDialogue = L"아, 그리고 상자 위에 올라갈 수도 있으니 잘 활용해보렴.";
			break;
		case 2:
			m_strDialogue = L"또 상자에 대해 궁금한 점이 있다면 나에게 물어보려무나.";
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

