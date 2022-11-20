#include "framework.h"
#include "CGrandma.h"

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


CGrandma::CGrandma(CPlayer* player)
{
	pPlayer = player;
	m_vecScale = Vector(18, 32);
	m_strDialogue = L"";
	talk = 0;
}

CGrandma::~CGrandma()
{
}

void CGrandma::Init()
{

	m_pImage = RESOURCE->LoadImg(L"Grandma_Idle", L"Image\\Grandma_Idle.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"Grandma_Idle_Right", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.3, 2);
	m_pAnimator->CreateAnimation(L"Grandma_Idle_Left", m_pImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.3, 2);

	m_pAnimator->Play(L"Grandma_Idle_Right");
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 0.1, m_vecScale.y - 0.1), Vector(0, 4));
}

void CGrandma::Update()
{
	if (talk > 0)
	{
		if (BUTTONDOWN('X'))
		{
			CSound* pSe = RESOURCE->FindSound(L"Dialogue");
			SOUND->Play(pSe, 0.5);
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

void CGrandma::Render()
{
	if (talk > 0)
	{
		pTalkBox->m_choose = &this->m_choose;
		pTalkBox->m_choosing = &this->m_choosing;
		pTalkBox->m_strDialogue = this->m_strDialogue;

	}
}

void CGrandma::Release()
{
}

void CGrandma::OnCollisionStay(CCollider* pOtherCollider)
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
			pPlayer->SetDir(Vector( - 1, 0));
			pPlayer->m_behavior = Behavior::Talk;

			pTalkBox = new CTalkBox;
			pTalkBox->SetPos(this->GetPos());
			ADDOBJECT(pTalkBox);
		}
	}
}

void CGrandma::Talk()
{
	if (changeTalkTopic == 0)
	{
		switch (talk)
		{
		case 0:
			m_strDialogue = L"";
			break;
		case 1:
			m_strDialogue = L"아이고 허리야.. 슈퍼에서 뭘 사야하나..";
			break;
		case 2:
			m_strDialogue = L"흐음 어디보자..";
			break;
		case 3:
			m_strDialogue = L"아이고, 눈이 안좋아서 안보이네..";
			break;
		case 4:
			m_strDialogue = L"여보게나. 자네가 한번 봐줄수 있나? \n\n 싫어요.\n 페로알이라고 쓰여있어요.";
			m_choose = 2;
			break;
		case 5:
			if (m_choosing == 1)
			{
				m_strDialogue = L"뭐어? 이런 버르장머리없는 놈을 봤나!";
			}
			else
			{
				m_strDialogue = L"도와줘서 고맙구나. 이건 답례란다.";
				GAME->PushBackInvenItem(L"벌꿀");
			}
			m_choose = 0;
			m_choosing = 1;
			break;
		default:
			CAMERA->ZoomInOut(2, 1);
			m_strDialogue = L"";
			changeTalkTopic++;
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
			m_strDialogue = L"아이고.. 늙으면 죽어야지..";
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
