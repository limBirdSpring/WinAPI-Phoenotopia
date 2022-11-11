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
	if (m_strDialogue != L"")
	{
		if (m_strDialogue.length() > 25)
		{
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
		break;
	}
}
