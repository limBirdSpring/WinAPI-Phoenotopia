#include "framework.h"
#include "CThief2.h"


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


CThief2::CThief2(CPlayer* player)
{
	pPlayer = player;
	m_vecScale = Vector(18, 32);
	m_strDialogue = L"";
	talk = 0;
}

CThief2::~CThief2()
{
}

void CThief2::Init()
{

	m_pImage = RESOURCE->LoadImg(L"Thief2", L"Image\\Thief2.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"Thief2_Idle", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.2, 2);
	m_pAnimator->Play(L"Thief2_Idle");
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 0.1, m_vecScale.y - 0.1), Vector(0, 4));
}

void CThief2::Update()
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

void CThief2::Render()
{
	if (talk > 0)
	{
		pTalkBox->m_choose = &this->m_choose;
		pTalkBox->m_choosing = &this->m_choosing;
		pTalkBox->m_strDialogue = this->m_strDialogue;

	}
}

void CThief2::Release()
{
}

void CThief2::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"�÷��̾�")
	{
		if (BUTTONDOWN('X'))
		{
			CAMERA->ZoomInOut(2.5, 1);

			talk++;
			GAME->SetTalk(true);
			Talk();
			pOtherCollider->GetOwner()->SetPos(m_vecPos.x - 30, m_vecPos.y);
			pPlayer->SetDir(Vector(1, 0));
			pPlayer->m_behavior = Behavior::Talk;

			pTalkBox = new CTalkBox;
			pTalkBox->SetPos(this->GetPos());
			ADDOBJECT(pTalkBox);
		}
	}
}

void CThief2::Talk()
{
	if (changeTalkTopic == 0)
	{
		switch (talk)
		{
		case 0:
			m_strDialogue = L"";
			break;
		case 1:
			m_strDialogue = L"����. �� ���� ã�� ����?";
			break;
		case 2:
			m_strDialogue = L"������. �� �׷��� ���ۻ�� �ƴ϶�.";
			break;
		case 3:
			m_strDialogue = L"�� 3���� 200G. �?";
			break;
		case 4:
			m_strDialogue = L"... \n\n 200G�� �ش�. \n �� ���۰����϶��!";
			m_choose = 2;
			break;
		case 5:
			if (m_choosing == 1)
			{
				if (GAME->GetGold() >= 200)
				{
					m_strDialogue = L"�̷��� ���� ������ �����°�? �� ���� �޾�.";
					GAME->SetGold(-200);
					GAME->PushBackInvenItem(L"��");
					GAME->PushBackInvenItem(L"��");
					GAME->PushBackInvenItem(L"��");
					changeTalkTopic++;
				}
				else
					m_strDialogue = L"�� �ִ� �� �¾�?";
			}
			else
			{
				m_strDialogue = L"��? ����? �� ���� '���� ������'���� ���ϱ�� �Ѱž�?";
			}
			m_choose = 0;
			break;
		case 6:
			if (m_choosing == 1)
			{
				CAMERA->ZoomInOut(2, 1);
				m_strDialogue = L"";
				GAME->SetTalk(false);
				talk = 0;
				DELETEOBJECT(pTalkBox);
			}
			else
			{
				m_strDialogue = L"�� �༮���� �����ϰ� ���� ������ ���� �츮 '�ʷ� ������'���� �ٸ��� �������� �ؼ� ���� ���ٰ�!";
			}
			m_choosing = 1;
			break;
		case 7:
			m_strDialogue = L"��, ���� �츮 '�ʷ� ������'�� �����̱� ������! ũ��";
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

	else if (changeTalkTopic == 1)
	{
		switch (talk)
		{
		case 0:
			m_strDialogue = L"";
			break;
		case 1:
			m_strDialogue = L"�װ� �� ���� ���� ���� ��~�� ���� ������ ����!";
			break;
		case 2:
			m_strDialogue = L"�׷� ����� ��ٰ�!";
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
