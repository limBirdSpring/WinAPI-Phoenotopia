#include "framework.h"
#include "CBuyEvent.h"

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


CBuyEvent::CBuyEvent(CPlayer* player)
{
	pPlayer = player;
	m_vecScale = Vector(18, 32);
	m_strDialogue = L"";
	talk = 0;
}

CBuyEvent::~CBuyEvent()
{
}

void CBuyEvent::Init()
{
	m_pImage = RESOURCE->LoadImg(L"UI_!", L"Image\\UI_!.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"UI_!", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.1, 6);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 0.1, m_vecScale.y - 0.1), Vector(0, 4));
}

void CBuyEvent::Update()
{

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

void CBuyEvent::Render()
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

	RENDER->Image(item.img, m_vecPos.x - 20, m_vecPos.y - 20, m_vecPos.x + 20, m_vecPos.y + 20);
}

void CBuyEvent::Release()
{
}

void CBuyEvent::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		m_pAnimator->Play(L"UI_!");

		if (BUTTONDOWN('X'))
		{
			talk++;
			GAME->SetTalk(true);
			pPlayer->m_behavior = Behavior::Talk;
			Talk();
		}
	}
}

void CBuyEvent::OnCollisionExit(CCollider* pOtherCollider)
{
	m_pAnimator->Stop();
}

void CBuyEvent::Talk()
{
	
	switch (talk)
	{
	case 0:
		m_strDialogue = L"";
		break;
	case 1:
		m_strDialogue = to_wstring(item.price) + L"G에 " + item.name + L"을(를) 살까?  \n\n 네. \n 아니요.";
		m_choose = 2;
		m_choosing = 1;
		break;
	case 2:
	{
		if (m_choosing == 1)
		{
			if (GAME->GetGold() < item.price)
			{
				m_strDialogue = L"돈이 부족합니다.";
			}
			else if (GAME->m_vInventoryItem.size() > 12)
			{
				m_strDialogue = L"인벤토리가 꽉 찼습니다.";
			}
			else
			{
				GAME->SetGold(-item.price);
				GAME->PushBackInvenItem(item);
				m_strDialogue = item.name + L"을(를) 구매했다.";
			}
		}
		else
		{
			m_strDialogue = L"";
			GAME->SetTalk(false);
			talk = 0;
			break;
		}
		m_choose = 0;
		m_choosing = 1;
		break;
	}
	default:
		m_strDialogue = L"";
		GAME->SetTalk(false);
		talk = 0;
		break;
	}
}
