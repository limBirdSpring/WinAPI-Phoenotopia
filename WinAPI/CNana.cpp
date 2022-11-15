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
			DELETEOBJECT(pTalkBox);
			break;
		}
	}
}

