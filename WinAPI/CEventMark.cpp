#include "framework.h"
#include "CEventMark.h"

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

CEventMark::CEventMark(CPlayer* player)
{
	pPlayer = player;
	m_vecScale = Vector(18, 32);
	m_strDialogue = L"";
	m_strSetDialogue = L"";
	talk = 0;
}

CEventMark::~CEventMark()
{
}

void CEventMark::Init()
{
	m_pImage = RESOURCE->LoadImg(L"UI_!", L"Image\\UI_!.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"UI_!", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.1, 6);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 0.1, m_vecScale.y - 0.1), Vector(0, 4));
}

void CEventMark::Update()
{
}

void CEventMark::Render()
{
	if (talk > 0)
	{
		pTalkBox->m_choose = &this->m_choose;
		pTalkBox->m_choosing = &this->m_choosing;
		pTalkBox->m_strDialogue = this->m_strDialogue;

	}
}

void CEventMark::Release()
{
}

void CEventMark::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		m_pAnimator->Play(L"UI_!");
		
		if (BUTTONDOWN('X'))
		{
			talk++;
			pPlayer->m_behavior = Behavior::Talk;
			GAME->SetTalk(true);
			Talk();

			if (pTalkBox == nullptr)
			{
				pTalkBox = new CTalkBox;
				pTalkBox->SetPos(this->GetPos());
				ADDOBJECT(pTalkBox);
			}
		}
	}
}

void CEventMark::OnCollisionExit(CCollider* pOtherCollider)
{
	m_pAnimator->Stop();
}

void CEventMark::Talk()
{
	switch (talk)
	{
	case 0:
		m_strDialogue = L"";
		break;
	case 1:
		m_strDialogue = m_strSetDialogue;
		break;
	
	default:
		m_strDialogue = L"";
		GAME->SetTalk(false);
		talk = 0;
		DELETEOBJECT(pTalkBox);
		break;
	}
}
