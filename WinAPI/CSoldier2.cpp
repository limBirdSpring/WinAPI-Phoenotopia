#include "framework.h"
#include "CSoldier2.h"

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


CSoldier2::CSoldier2(CPlayer* player)
{
	pPlayer = player;
	m_vecScale = Vector(18, 32);
	m_strDialogue = L"";
	talk = 0;
}

CSoldier2::~CSoldier2()
{
}

void CSoldier2::Init()
{

	m_pImage = RESOURCE->LoadImg(L"Soldier2_Idle", L"Image\\Soldier2_Idle.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"Soldier2_Idle_Right", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.2, 6);
	m_pAnimator->CreateAnimation(L"Soldier2_Idle_Left", m_pImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.2, 6);

	m_pAnimator->Play(L"Soldier2_Idle_Right");
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 0.1, m_vecScale.y - 0.1), Vector(0, 4));
}

void CSoldier2::Update()
{
	if (GAME->IsItemInvenItem(L"개구리 뒷다리"))
	{
		changeTalkTopic=1;
	}

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

	if (talk > 0)
	{
		pTalkBox->m_choose = &this->m_choose;
		pTalkBox->m_choosing = &this->m_choosing;
		pTalkBox->m_strDialogue = this->m_strDialogue;

	}
}

void CSoldier2::Render()
{


}

void CSoldier2::Release()
{
}

void CSoldier2::OnCollisionStay(CCollider* pOtherCollider)
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

void CSoldier2::Talk()
{
	if (changeTalkTopic == 0)
	{
		switch (talk)
		{
		case 0:
			m_strDialogue = L"";
			break;
		case 1:
			m_strDialogue = L"오늘도 돈을 꽤 많이 벌었구만. 역시 돈이 최고야~";
			break;
		case 2:
			m_strDialogue = L"뭐? 돈좀 달라고?";
			break;
		case 3:
			m_strDialogue = L"그냥은 못주지! 돈 되는 물건을 가져오면 몰라도.";

			break;
		case 4:
			m_strDialogue = L"음.. 그거면 될거 같은데. 개구리 뒷다리!";
			break;
		case 5:
			m_strDialogue = L"가져온다면 내가 비싼 값에 사주지!";
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
			m_strDialogue = L"응? 또 너냐?";
			break;
		case 2:
			m_strDialogue = L"무슨 볼일인데? \n\n '개구리 뒷다리'를 건넨다.\n 아무 것도 아니야.";
			m_choose = 2;
			break;
		case 3:
			if (m_choosing == 1)
			{
				m_strDialogue = L"오 진짜 가져왔네?";
			}
			else
			{
				m_strDialogue = L"싱겁긴.";

			}
			m_choose = 0;
			break;
		case 4:
			if (m_choosing == 1)
			{
				m_strDialogue = L"약속대로 원래 가격의 2배를 쳐주지. 여기 받아.";
				GAME->EraseInvenItem(L"개구리 뒷다리");
				GAME->SetGold(80);
			}
			else
			{
				CAMERA->ZoomInOut(2, 1);
				m_strDialogue = L"";
				changeTalkTopic++;
				GAME->SetTalk(false);
				talk = 0;
				DELETEOBJECT(pTalkBox);
			}
			m_choosing = 1;
			break;
		default:
			CAMERA->ZoomInOut(2, 1);
			m_strDialogue = L"";
			changeTalkTopic++;
			GAME->SetTalk(false);
			talk = 0;
			DELETEOBJECT(pTalkBox);
			changeTalkTopic++;
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
			m_strDialogue = L"아 돈 되는 일 또 없나~";
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
