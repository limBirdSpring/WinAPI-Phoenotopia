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


	if (talk > 0 && talk < 15)
	{
		if (BUTTONDOWN('X'))
		{
			talk++;
			Talk();
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
			m_pAnimator->Play(L"Leo_Strech_Left");
			m_strDialogue = L"��! ��¥ ���� ���Ϸ����ٴ�!";
			break;
		case 2:
			m_pAnimator->Play(L"Leo_Idle_Left");
			m_strDialogue = L"���� ����!";
			break;
		case 3:
			m_pAnimator->Play(L"Leo_Sleepy_Left");
			m_strDialogue = L"�ʹ� �����ؼ� ��ħ �׳� �������� ��Ƹ����� �ϴ� ���̾��µ�.";
			break;
		case 4:
			m_pAnimator->Play(L"Leo_Idle_Left");
			m_strDialogue = L"...";
			break;
		case 5:
			m_strDialogue = L"���� ���� �ձ����� ���ư����~";
			break;
		case 6:
			m_strDialogue = L"...";
			pPlayer->SetBehavior(Behavior::Bored);
			break;
		case 7:
			m_strDialogue = L"����? ���Ѽ��� �ʰ�.";
			break;
		case 8:
			pPlayer->SetBehavior(Behavior::Talk);
			m_strDialogue = L"\n\n ��������ũ ������? \n ��������ũ ����";
			m_choose = 2;
			break;
		case 9:
			m_choose = 0;
			m_strDialogue = L"�� �װ�? �װ� ����ĸ�..";
			break;
		case 10:
			m_pAnimator->Play(L"Leo_Sleepy_Left");
			m_strDialogue = L"���� ��ӿ� �ִ��϶�!";
			break;
		case 11:
			m_pAnimator->Play(L"Leo_Idle_Left");
			m_strDialogue = L"��ٸ��µ��� �谡���ļ� �̹� �� �Ծ������ ����.";
			break;
		case 12:
			m_pAnimator->Play(L"Leo_Strech_Left");
			m_strDialogue = L"�׷��� �������� �׷���?";
			break;
		case 13:
			m_strDialogue = L"";
			break;
		case 14:
			CAMERA->ZoomInOut(6);
			m_strDialogue = L"";
			break;
		case 15:
			pPlayer->SetBehavior(Behavior::Bat);
			break;
		}

}
