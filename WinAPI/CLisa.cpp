#include "framework.h"
#include "CLisa.h"

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


CLisa::CLisa(CPlayer* player)
{
	pPlayer = player;
	m_vecScale = Vector(18, 32);
	m_strDialogue = L"";
	talk = 0;
}

CLisa::~CLisa()
{
}

void CLisa::Init()
{

	m_pImage = RESOURCE->LoadImg(L"Lisa_Idle", L"Image\\Lisa_Idle.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"Lisa_Idle_Right", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.3, 2);
	m_pAnimator->CreateAnimation(L"Lisa_Idle_Left", m_pImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.3, 2);

	m_pAnimator->Play(L"Lisa_Idle_Left");
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 0.1, m_vecScale.y - 0.1), Vector(0, 4));
}

void CLisa::Update()
{
	if (talk > 0)
	{
		if (BUTTONDOWN('X'))
		{
			talk++;
			Talk();
		}
	}

	if (GAME->mainQuest == MainQuest::VisitStore)
		changeTalkTopic = 1;
	else
		changeTalkTopic = 0;
	
}

void CLisa::Render()
{
	if (talk > 0)
	{
		pTalkBox->m_choose = &this->m_choose;
		pTalkBox->m_choosing = &this->m_choosing;
		pTalkBox->m_strDialogue = this->m_strDialogue;

	}
}

void CLisa::Release()
{
}

void CLisa::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		if (BUTTONDOWN('X'))
		{
			CAMERA->ZoomInOut(3.5, 1);

			talk++;
			GAME->SetTalk(true);
			Talk();
			pOtherCollider->GetOwner()->SetPos(m_vecPos.x - 30, m_vecPos.y);
			pPlayer->m_vecMoveDir.x = 1;
			pPlayer->m_behavior = Behavior::Talk;

			pTalkBox = new CTalkBox;
			pTalkBox->SetPos(this->GetPos());
			ADDOBJECT(pTalkBox);
		}
	}
}

void CLisa::Talk()
{
	if (changeTalkTopic == 1)
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
			m_strDialogue = L"그러고보니, 밖에 새로운 전단지가 붙었다는데.";
			break;
		case 4:
			m_strDialogue = L"궁금하면 한번 가보는 것은 어때?";
			break;
		default:
			CAMERA->ZoomInOut(3, 1.5);
			m_strDialogue = L"";
			GAME->SetTalk(false);
			talk = 0;
			DELETEOBJECT(pTalkBox);
			break;
		}
	}
	else
	{
		switch (talk)
		{
		case 0:
			m_strDialogue = L"";
			break;
		case 1:
			m_strDialogue = L"어서오세요~ 판셀로 상점입니다!";
			break;
		case 2:
			m_strDialogue = L"게일 안녕! 뭐 필요한 거 있어?";
			break;
		default:
			CAMERA->ZoomInOut(3, 1.5);
			m_strDialogue = L"";
			GAME->SetTalk(false);
			talk = 0;
			DELETEOBJECT(pTalkBox);
			break;
		}
	}
}
