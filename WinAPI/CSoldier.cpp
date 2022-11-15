#include "framework.h"
#include "CSoldier.h"

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


CSoldier::CSoldier(CPlayer* player)
{
	pPlayer = player;
	m_vecScale = Vector(18, 32);
	m_strDialogue = L"";
	talk = 0;
}

CSoldier::~CSoldier()
{
}

void CSoldier::Init()
{

	m_pImage = RESOURCE->LoadImg(L"Soldier_Idle", L"Image\\Soldier_Idle.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"Soldier_Idle_Right", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.3, 2);
	m_pAnimator->CreateAnimation(L"Soldier_Idle_Left", m_pImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.3, 2);

	m_pAnimator->Play(L"Soldier_Idle_Left");
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 0.1, m_vecScale.y - 0.1), Vector(0, 4));
}

void CSoldier::Update()
{
	if (GAME->isItemSetting(L"방망이"))
	{
		changeTalkTopic = 1;
	}

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

	if (talk > 0)
	{
		pTalkBox->m_choose = &this->m_choose;
		pTalkBox->m_choosing = &this->m_choosing;
		pTalkBox->m_strDialogue = this->m_strDialogue;

	}
}

void CSoldier::Render()
{

	
}

void CSoldier::Release()
{
}

void CSoldier::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어")
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

void CSoldier::Talk()
{
	if (changeTalkTopic == 0)
	{
		switch (talk)
		{
		case 0:
			m_strDialogue = L"";
			break;
		case 1:
			m_strDialogue = L"아.. 게일 안녕. 뭐하고 있냐고? \n보면 알잖아. 더비숲으로 가는 문을 지키는 중이야.";
			break;
		case 2:
			m_strDialogue = L"뭐? 이 너머로 지나가고 싶다고?";
			break;
		case 3:
			m_strDialogue = L"무기도 없이 가면 위험할 거야.";
			break;
		case 4:
			m_strDialogue = L"난 자격이 되는 자에게만 문을 열어주지.";
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
			m_strDialogue = L"오. 그거 무기야? 그럼 문을 여는 방법을 알려줄게.";
			break;
		case 2:
			m_strDialogue = L"무기를 사용해서 수정구슬을 치면 문이 열릴 거야.";
			break;
		case 3:
			m_strDialogue = L"더비숲에는 위험한 몬스터들이 많으니까 조심해.";
			break;
		case 4:
			m_strDialogue = L"행운을 빌어.";
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
			m_strDialogue = L"안녕 게일... 이렇게 가만히 서있으니까 정말 따분하네.";
			break;
		case 2:
			m_strDialogue = L"더비숲에서 재밌는 일이 생기면 나중에 들려줘.";
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
