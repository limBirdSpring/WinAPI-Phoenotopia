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
	if (GAME->IsItemInvenItem(L"������ �޴ٸ�"))
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
	if (pOtherCollider->GetObjName() == L"�÷��̾�")
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
			m_strDialogue = L"���õ� ���� �� ���� ��������. ���� ���� �ְ��~";
			break;
		case 2:
			m_strDialogue = L"��? ���� �޶��?";
			break;
		case 3:
			m_strDialogue = L"�׳��� ������! �� �Ǵ� ������ �������� ����.";

			break;
		case 4:
			m_strDialogue = L"��.. �װŸ� �ɰ� ������. ������ �޴ٸ�!";
			break;
		case 5:
			m_strDialogue = L"�����´ٸ� ���� ��� ���� ������!";
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
			m_strDialogue = L"��? �� �ʳ�?";
			break;
		case 2:
			m_strDialogue = L"���� �����ε�? \n\n '������ �޴ٸ�'�� �ǳٴ�.\n �ƹ� �͵� �ƴϾ�.";
			m_choose = 2;
			break;
		case 3:
			if (m_choosing == 1)
			{
				m_strDialogue = L"�� ��¥ �����Գ�?";
			}
			else
			{
				m_strDialogue = L"�̰̱�.";

			}
			m_choose = 0;
			break;
		case 4:
			if (m_choosing == 1)
			{
				m_strDialogue = L"��Ӵ�� ���� ������ 2�踦 ������. ���� �޾�.";
				GAME->EraseInvenItem(L"������ �޴ٸ�");
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
			m_strDialogue = L"�� �� �Ǵ� �� �� ����~";
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
