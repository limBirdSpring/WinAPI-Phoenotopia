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
	if (GAME->IsItemInvenItem(L"방망이") || GAME->isItemSetting(L"방망이"))
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
			m_strDialogue = L"이봐. 너 더비숲으로 가는 문을 열고 싶지?";
			break;
		case 2:
			m_strDialogue = L"보아하니 무기도 없는 것 같은데..";
			break;
		case 3:
			m_strDialogue = L"내가 문도 열어주고 거기에 무기까지 주도록 하지.";
			break;
		case 4:
			m_strDialogue = L"80G만 주면 말이야. 어때? 이정도면 꽤 좋은 제안 아니야?";
			break;

		case 5:
			m_strDialogue = L"... \n\n 80G를 준다. \n 괜찮아요.";
			m_choose = 2;
			break;
		case 6:
			if (m_choosing == 1)
			{
				if (GAME->GetGold() >= 80)
				{
					m_strDialogue = L"말이 잘 통하는 녀석이군. 잘 속기까지 하고 말이야~ 그럼 이만!";
					GAME->SetGold(-80);
					isRun = true;
					pSe = RESOURCE->FindSound(L"Run");
					SOUND->Play(pSe);
				}
				else
					m_strDialogue = L"이봐. 돈이 부족하잖아! 80G라고.";
			}
			else
			{
				m_strDialogue = L"아쉽군. 꽤 좋은 제안이라고 생각했는데.";
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
