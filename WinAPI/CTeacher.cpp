#include "framework.h"
#include "CTeacher.h"

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


CTeacher::CTeacher(CPlayer* player)
{
	pPlayer = player;
	m_vecScale = Vector(18, 32);
	m_strDialogue = L"";
	talk = 0;
}

CTeacher::~CTeacher()
{
}

void CTeacher::Init()
{

	m_pImage = RESOURCE->LoadImg(L"Teacher_Idle", L"Image\\Teacher_Idle.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"Teacher_Idle_Right", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.5, 4);
	m_pAnimator->CreateAnimation(L"Teacher_Idle_Left", m_pImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.5, 4);

	m_pAnimator->Play(L"Teacher_Idle_Left");
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 0.1, m_vecScale.y - 0.1), Vector(0, 4));
}

void CTeacher::Update()
{
	if (changeTalkTopic == 1 && GAME->isItemSetting(L"�����"))
	{
		changeTalkTopic++;
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
}

void CTeacher::Render()
{
	if (talk > 0)
	{
		pTalkBox->m_choose = &this->m_choose;
		pTalkBox->m_choosing = &this->m_choosing;
		pTalkBox->m_strDialogue = this->m_strDialogue;

	}
	
}

void CTeacher::Release()
{
}

void CTeacher::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"�÷��̾�")
	{
		if (BUTTONDOWN('X'))
		{
			CAMERA->ZoomInOut(2.5, 1);

			talk++;
			GAME->SetTalk(true);
			Talk();
			pPlayer->m_vecPos.x = this->m_vecPos.x - 30;
			pPlayer->m_vecMoveDir.x = 1;
			pPlayer->m_behavior = Behavior::Talk;
			
			pTalkBox = new CTalkBox;
			pTalkBox->SetPos(this->GetPos());
			ADDOBJECT(pTalkBox);
		}
	}
}

void CTeacher::Talk()
{
	if (changeTalkTopic == 0)
	{
		switch (talk)
		{
		case 0:
			m_strDialogue = L"";
			break;
		case 1:
			m_strDialogue = L"��. ���ϿԱ���. �� ���Ⱑ �� ���鱸��.";
			break;
		case 2:
			m_strDialogue = L"������ �� �ϰ� �ֳ�? �ƴ�, �׷����� ����. �̷��� �п��� �ȳ����µ�.";
			break;
		case 3:
			m_strDialogue = L"��? ���⸦ ������ �Դٰ�? ���� �Ҿ�����ų�?";
			break;
		case 4:
			m_strDialogue = L"��, ����. �׷�. �ٽ� ���״� ��� ���� ������ �����ؾ��Ѵ�. �������ؼ��� �ȵ�.";
			break;
		case 5:
			m_strDialogue = L"��. ���� �ްŶ�.";
			GAME->PushBackInvenItem(L"�����");
			break;
		case 6:
			m_strDialogue = L"�� ��. ���⸦ �����ϴ� ����� ���� �� �ƴϰ���?";
			break;
		case 7:
			m_strDialogue = L"I�� ���� �κ��丮�� �� ���⸦ ������ �� X�� ������ ���� ��ư�� ���´ܴ�.";
			break;
		case 8:
			m_strDialogue = L"��. �ѹ� �غ���.";
			break;
		default:
			CAMERA->ZoomInOut(2, 1);
			m_strDialogue = L"";
			GAME->SetTalk(false);
			talk = 0;
			changeTalkTopic++;
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
			m_strDialogue = L"I�� ���� �κ��丮�� �� ���⸦ ������ �� X�� ������ ���� ��ư�� ���´ܴ�.";
			break;
		case 2:
			m_strDialogue = L"��. �ѹ� �غ���.";
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
	else if (changeTalkTopic == 2)
	{
		switch (talk)
		{
		case 0:
			m_strDialogue = L"";
			break;
		case 1:
			m_strDialogue = L"��? ���� �⺻���� ���� ���۵� �ؾ������ �ƴϰ���?";
			break;
		case 2:
			m_strDialogue = L"����. �׷� �˾Ҵ�. 2�� �ȳ������� �׷��� ����.";
			break;
		case 3:
			m_strDialogue = L"ó������ �˷����״� �� ��Ŷ�.";
			break;
		case 4:
			m_strDialogue = L"���⸦ ������ ���¿��� XŰ�� ������ ���⸦ �ֵθ� �� �ִܴ�.";
			break;
		case 5:
			m_strDialogue = L"������ �ϸ� XŰ�� ������ �Ϲݰ��ݺ��� ������ �� ���߰����� �� �� ����.";
			break;
		case 6:
			m_strDialogue = L"��. ���� ���ÿ� �����װ� ������, �ѹ� �����غ���.";
			break;
		case 7:
			m_strDialogue = L"�����״� ������ ���� �ƴϳİ�?";
			break;
		case 8:
			m_strDialogue = L"�׷�. ������ �� �����״� ���������� ��鿩���� �ƹ��� �������� ������ ���Ѵܴ�.";
			break;
		case 9:
			m_strDialogue = L"������ �߻� �����״� ������ �ص� �������� ���� �ʴ� ���ù����� �����̴� ������ ������ ���� �ʴ°� ���ܴ�.";
			break;
		case 10:
			m_strDialogue = L"����� ������ �ߴٸ� ������ �ٽ� ���� �ɰŶ�.";
			break;
		case 11:
			m_strDialogue = L"�׷� ���� ����� ũ��Ƽ�� ���ݿ� ���� ����������.";
			break;
		default:
			CAMERA->ZoomInOut(2, 1);
			m_strDialogue = L"";
			GAME->SetTalk(false);
			talk = 0;
			changeTalkTopic++;
			DELETEOBJECT(pTalkBox);
			break;
		}
	}
	else if (changeTalkTopic == 3)
	{
		switch (talk)
		{
		case 0:
			m_strDialogue = L"";
			break;
		case 1:
			m_strDialogue = L"����� ������ �߰���?";
			break;
		case 2:
			m_strDialogue = L"������ ũ��Ƽ�� �����̴�. ũ��Ƽ�� ������ ���� ������ ����.";
			break;
		case 3:
			m_strDialogue = L"XŰ�� �����ð����� ������ ������ ���⿡ ��¡�������� ä�����ܴ�.";
			break;
		case 4:
			m_strDialogue = L"�� ���¿��� XŰ�� ���� ũ��Ƽ�� ������ �ߵ�����.";
			break;
		case 5:
			m_strDialogue = L"ũ��Ƽ�� ������ ������ ������, �����غ� �ð����ȿ��� �̵��ӵ��� �������� �����ؼ� ����Ѵܴ�.";
			break;
		case 6:
			m_strDialogue = L"��. �̹����� �ѹ� �����غ��Ŷ�.";
			break;
		default:
			CAMERA->ZoomInOut(2, 1);
			m_strDialogue = L"";
			GAME->SetTalk(false);
			talk = 0;
			changeTalkTopic++;
			DELETEOBJECT(pTalkBox);
			break;
		}
	}
	else if (changeTalkTopic == 4)
	{
		switch (talk)
		{
		case 0:
			m_strDialogue = L"";
			break;
		case 1:
			m_strDialogue = L"�׷�. �������� ����� ������ �Ǿ�����.";
			break;
		case 2:
			m_strDialogue = L"�����ε� �п��� ������ ���ͼ� ������ �ϵ��� �Ϸ�.";
			break;
		default:
			CAMERA->ZoomInOut(2, 1);
			m_strDialogue = L"";
			GAME->SetTalk(false);
			talk = 0;
			changeTalkTopic++;
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
		m_strDialogue = L"�������̳� ����?";
		break;
	case 2:
		m_strDialogue = L"�� ���� �����Ϸ� �°ų�? ������ �ذ� ���ʿ��� �߰ڱ���.";
		break;
	case 3:
		m_strDialogue = L"\n\n ���ݿ� ���� �ٽ� ���;��.\n �ȳ����輼��.";
		m_choose = 2;
		break;
	case 4:
		if (m_choosing == 1)
		{
			m_strDialogue = L"�� ������ų�? �˰ڴ�. ������ �ٽ� ���� �ɰŶ�.";
			changeTalkTopic = 2;
		}
		else
		{
			m_strDialogue = L"�׷�. �߰���.";
		}
		m_choose = 0;
		m_choosing = 1;
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
