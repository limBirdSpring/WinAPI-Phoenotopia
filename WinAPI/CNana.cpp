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
#include "CTalkBox.h"


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
	if (talk > 0)
	{
		pTalkBox->m_choose = &this->m_choose;
		pTalkBox->m_choosing = &this->m_choosing;
		pTalkBox->m_strDialogue = this->m_strDialogue;

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

			pTalkBox = new CTalkBox;
			pTalkBox->SetPos(this->GetPos());
			ADDOBJECT(pTalkBox);
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
			DELETEOBJECT(pTalkBox);
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
			DELETEOBJECT(pTalkBox);
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
			DELETEOBJECT(pTalkBox);
			break;
		}
	}
}

