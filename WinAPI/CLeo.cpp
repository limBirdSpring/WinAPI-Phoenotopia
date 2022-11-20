#include "framework.h"
#include "CLeo.h"

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


CLeo::CLeo(CPlayer* player)
{
	pPlayer = player;
	m_vecScale = Vector(18, 32);
	m_strDialogue = L"";
	talk = 0;
	coolTime = 0;
}

CLeo::~CLeo()
{
}

void CLeo::Init()
{

	m_pAnimator = new CAnimator;

	m_pImage = RESOURCE->LoadImg(L"Leo_Idle", L"Image\\Leo_Idle.png");
	m_pAnimator->CreateAnimation(L"Leo_Idle_Right", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.3, 2);
	m_pAnimator->CreateAnimation(L"Leo_Idle_Left", m_pImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.3, 2);

	m_pImage = RESOURCE->LoadImg(L"Leo_Sleepy", L"Image\\Leo_Sleepy.png");
	m_pAnimator->CreateAnimation(L"Leo_Sleepy_Right", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.3, 2);
	m_pAnimator->CreateAnimation(L"Leo_Sleepy_Left", m_pImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.3, 2);

	m_pImage = RESOURCE->LoadImg(L"Leo_Strech", L"Image\\Leo_Strech.png");
	m_pAnimator->CreateAnimation(L"Leo_Strech_Right", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.3, 2);
	m_pAnimator->CreateAnimation(L"Leo_Strech_Left", m_pImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.3, 2);

	m_pAnimator->Play(L"Leo_Idle_Left");
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 0.1, m_vecScale.y - 0.1), Vector(0, 4));
}

void CLeo::Update()
{
	if (GAME->mainQuest == MainQuest::SavePrince && talk ==0)
	{
		pPlayer->SetBehavior(Behavior::Talk);
		talk++;
		GAME->SetTalk(true);
		Talk();

		pTalkBox = new CTalkBox;
		pTalkBox->SetPos(this->GetPos());
		ADDOBJECT(pTalkBox);
	}


	if (talk > 0 && talk < 13)
	{
		if (BUTTONDOWN('X'))
		{
			CSound* pSe = RESOURCE->FindSound(L"Dialogue");
			SOUND->Play(pSe, 0.5);
			talk++;
			Talk();
		}
	}
	if (coolTime > 0)
	{
		coolTime -= DT;

		if (coolTime < 3)
			CAMERA->ZoomInOut(6);

		if (coolTime < 1)
		{
			pPlayer->SetBehavior(Behavior::Bat);
		}
	}


}

void CLeo::Render()
{
	if (talk > 0 && talk < 14)
	{
		pTalkBox->m_choose = &this->m_choose;
		pTalkBox->m_choosing = &this->m_choosing;
		pTalkBox->m_strDialogue = this->m_strDialogue;

	}
}

void CLeo::Release()
{
}

void CLeo::OnCollisionStay(CCollider* pOtherCollider)
{

}

void CLeo::Talk()
{
	switch (talk)
	{
	case 0:
		m_strDialogue = L"";
		break;
	case 1:
	{
		CSound* pBgm = RESOURCE->FindSound(L"Fun");
		SOUND->Play(pBgm, 1, true);
		m_pAnimator->Play(L"Leo_Strech_Left");
		m_strDialogue = L"와! 진짜 짐을 구하러오다니!";
		break;
	}
	case 2:
		m_pAnimator->Play(L"Leo_Idle_Left");
		m_strDialogue = L"고맙다 서민!";
		break;
	case 3:
		m_pAnimator->Play(L"Leo_Sleepy_Left");
		m_strDialogue = L"너무 지루해서 마침 그냥 괴물한테 잡아먹힐까 하던 참이었는데.";
		break;
	case 4:
		m_pAnimator->Play(L"Leo_Idle_Left");
		m_strDialogue = L"...";
		break;
	case 5:
		m_strDialogue = L"이제 슬슬 왕궁으로 돌아가볼까나~";
		break;
	case 6:
		m_strDialogue = L"...";
		pPlayer->SetBehavior(Behavior::Bored);
		break;
	case 7:
		m_strDialogue = L"뭐해? 비켜서지 않고.";
		break;
	case 8:
		pPlayer->SetBehavior(Behavior::Talk);
		m_strDialogue = L"\n\n 딸기케이크 어딨어요? \n 딸기케이크 내놔";
		m_choose = 2;
		break;
	case 9:
		m_choose = 0;
		m_strDialogue = L"아 그거? 그게 어딨냐면..";
		break;
	case 10:
		m_pAnimator->Play(L"Leo_Sleepy_Left");
		m_strDialogue = L"짐의 뱃속에 있느니라!";
		break;
	case 11:
		m_pAnimator->Play(L"Leo_Idle_Left");
		m_strDialogue = L"기다리는동안 배가고파서 이미 다 먹어버렸지 뭐야.";
		break;
	case 12:
		m_pAnimator->Play(L"Leo_Strech_Left");
		m_strDialogue = L"그러게 빨리오지 그랬어?";
		break;
	case 13:
	{
		CSound* pBgm = RESOURCE->FindSound(L"Fun");
		SOUND->Stop(pBgm);
		coolTime = 5;
		m_strDialogue = L"";
		break;
	}
	}
}
