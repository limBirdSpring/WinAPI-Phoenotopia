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
#include "CTalkBox.h"


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

}

void CBuyEvent::Render()
{
	//������ ���� �߰�
	RENDER->Image(item.img, m_vecPos.x - 20, m_vecPos.y - 20, m_vecPos.x + 20, m_vecPos.y + 20);

	if (talk > 0)
	{
		pTalkBox->m_choose = &this->m_choose;
		pTalkBox->m_choosing = &this->m_choosing;
		pTalkBox->m_strDialogue = this->m_strDialogue;

	}
}

void CBuyEvent::Release()
{
}

void CBuyEvent::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"�÷��̾�")
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
	{
		pTalkBox = new CTalkBox;
		pTalkBox->SetPos(this->GetPos());
		ADDOBJECT(pTalkBox);

		m_strDialogue = to_wstring(item.price) + L"G�� " + item.name + L"��(��) ���?  \n\n ��. \n �ƴϿ�.";
		m_choose = 2;
		m_choosing = 1;
		break;
	}
	case 2:
	{
		if (m_choosing == 1)
		{
			if (GAME->GetGold() < item.price)
			{
				m_strDialogue = L"���� �����մϴ�.";
			}
			else if (GAME->m_vInventoryItem.size() > 12)
			{
				m_strDialogue = L"�κ��丮�� �� á���ϴ�.";
			}
			else
			{
				pSe = RESOURCE->FindSound(L"Buy");
				SOUND->Play(pSe);
				GAME->SetGold(-item.price);
				GAME->PushBackInvenItem(item);
				m_strDialogue = item.name + L"��(��) �����ߴ�.";
			}
		}
		else
		{
			m_strDialogue = L"";
			GAME->SetTalk(false);
			talk = 0;
			DELETEOBJECT(pTalkBox);
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
		DELETEOBJECT(pTalkBox);
		break;
	}
}
