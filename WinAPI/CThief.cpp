#include "framework.h"
#include "CThief.h"

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


CThief::CThief(CPlayer* player)
{
	pPlayer = player;
	m_vecScale = Vector(18, 32);
	m_strDialogue = L"";
	talk = 0;
	isRun = false;
}

CThief::~CThief()
{
}

void CThief::Init()
{

	m_pImage = RESOURCE->LoadImg(L"Thief", L"Image\\Thief.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"Thief_Idle", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.2, 2);
	m_pAnimator->CreateAnimation(L"Thief_Run", m_pImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.1, 6);

	m_pAnimator->Play(L"Thief_Idle");
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 0.1, m_vecScale.y - 0.1), Vector(0, 4));
}

void CThief::Update()
{
	if (GAME->IsItemInvenItem(L"�����") || GAME->isItemSetting(L"�����"))
		DELETEOBJECT(this);

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



	if (isRun)
	{
		m_pAnimator->Play(L"Thief_Run");
		m_vecPos.x -= DT * 200;
		coolTime += DT;

		if (coolTime > 2)
		{
			CAMERA->ZoomInOut(2, 1);
			m_strDialogue = L"";
			GAME->SetTalk(false);
			talk = 0;
			DELETEOBJECT(pTalkBox);
			DELETEOBJECT(this);
		}
	}

}

void CThief::Render()
{
	if (talk > 0)
	{
		pTalkBox->m_choose = &this->m_choose;
		pTalkBox->m_choosing = &this->m_choosing;
		pTalkBox->m_strDialogue = this->m_strDialogue;

	}
}

void CThief::Release()
{
}

void CThief::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"�÷��̾�")
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

void CThief::Talk()
{
	if (changeTalkTopic == 0)
	{
		switch (talk)
		{
		case 0:
			m_strDialogue = L"";
			break;
		case 1:
			m_strDialogue = L"�̺�. �� �������� ���� ���� ���� ����?";
			break;
		case 2:
			m_strDialogue = L"�����ϴ� ���⵵ ���� �� ������..";
			break;
		case 3:
			m_strDialogue = L"���� ���� �����ְ� �ű⿡ ������� �ֵ��� ����.";
			break;
		case 4:
			m_strDialogue = L"80G�� �ָ� ���̾�. �? �������� �� ���� ���� �ƴϾ�?";
			break;

		case 5:
			m_strDialogue = L"... \n\n 80G�� �ش�. \n �����ƿ�.";
			m_choose = 2;
			break;
		case 6:
			if (m_choosing == 1)
			{
				if (GAME->GetGold() >= 80)
				{
					m_strDialogue = L"���� �� ���ϴ� �༮�̱�. �� �ӱ���� �ϰ� ���̾�~ �׷� �̸�!";
					GAME->SetGold(-80);
					isRun = true;
					pSe = RESOURCE->FindSound(L"Run");
					SOUND->Play(pSe);
				}
				else
					m_strDialogue = L"�̺�. ���� �������ݾ�! 80G���.";
			}
			else
			{
				m_strDialogue = L"�ƽ���. �� ���� �����̶�� �����ߴµ�.";
			}
			m_choose = 0;
			m_choosing = 1;
			break;
		default:
			CAMERA->ZoomInOut(2, 1);
			m_strDialogue = L"";
			GAME->SetTalk(false);
			talk = 0;
			DELETEOBJECT(pTalkBox);
			break;
		}
	}

}
