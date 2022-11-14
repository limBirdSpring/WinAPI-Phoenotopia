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
	if (pOtherCollider->GetObjName() == L"�÷��̾�")
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
			m_strDialogue = L"��, ���ϿԱ���. ������ ��ħ ������ ������, ��� �����?";
			break;
		case 2:
			m_strDialogue = L"�� �´�. �׷����� �˷��ٰ��� �ִܴ�.";
			break;
		case 3:
			m_strDialogue = L"�� Ȥ�� ���� �̴� ���� ���� �ƴ�?";
			break;
		case 4:
			m_strDialogue = L"AŰ�� ������ ���ڿ� �����ϸ� �ȴܴ�. �ѹ� �غ���.";
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
			m_strDialogue = L"��? ū ���ڴ� �� �и��ٰ�? ����..";
			break;
		case 2:
			m_strDialogue = L"ū ���ڴ� ���� �ʿ��� �ʹ� ���ſ������.";
			break;
		case 3:
			m_strDialogue = L"��� ū ���ڴ� ������ �Ͽ� �μ� �� �ִܴ�.";
			break;
		case 4:
			m_strDialogue = L"���� ������ �������� ����ֱ⵵ ����.";
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
			m_strDialogue = L"��, �׸��� ���� ���� �ö� ���� ������ �� Ȱ���غ���.";
			break;
		case 2:
			m_strDialogue = L"�� ���ڿ� ���� �ñ��� ���� �ִٸ� ������ ���������.";
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

