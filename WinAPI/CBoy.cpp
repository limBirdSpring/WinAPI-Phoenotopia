#include "framework.h"
#include "CBoy.h"

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
#include "CLineMove.h"


CBoy::CBoy(CPlayer* player)
{
	pPlayer = player;
	m_vecScale = Vector(18, 32);
	m_strDialogue = L"";
	talk = 0;
}

CBoy::~CBoy()
{
}

void CBoy::Init()
{
	m_pAnimator = new CAnimator;

	m_pImage = RESOURCE->LoadImg(L"Boy_Idle", L"Image\\Boy_Idle.png");
	m_pAnimator->CreateAnimation(L"Boy_Idle_Right", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.3, 2);
	m_pAnimator->CreateAnimation(L"Boy_Idle_Left", m_pImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.3, 2);

	m_pImage = RESOURCE->LoadImg(L"Boy_Walk", L"Image\\Boy_Walk.png");
	m_pAnimator->CreateAnimation(L"Boy_Walk_Right", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.3, 6);
	m_pAnimator->CreateAnimation(L"Boy_Walk_Left", m_pImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.3, 6);

	m_pAnimator->Play(L"Boy_Idle_Right");

	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 0.1, m_vecScale.y - 0.1), Vector(0, 4));
}

void CBoy::Update()
{
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

void CBoy::Render()
{
	if (talk > 0)
	{
		pTalkBox->m_choose = &this->m_choose;
		pTalkBox->m_choosing = &this->m_choosing;
		pTalkBox->m_strDialogue = this->m_strDialogue;

	}
}

void CBoy::Release()
{
}

void CBoy::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"�÷��̾�")
	{
		if (BUTTONDOWN('X'))
		{
			CAMERA->ZoomInOut(2.5, 1);

			m_pAnimator->Play(L"Boy_Idle_Right");
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

void CBoy::Talk()
{
	if (changeTalkTopic == 0)
	{
		switch (talk)
		{
		case 0:
			m_strDialogue = L"";
			break;
		case 1:
			m_strDialogue = L"�ȳ��ϼ���!";
			break;
		case 2:
			m_strDialogue = L"������ ���̰� ���� ����� ���� �λ��ؾ��Ѵٰ� �߰ŵ��!";
			break;
		case 3:
			m_strDialogue = L"��.. ��! ���� ����ִ� ��о�⸦ �ϳ� �˰��ִµ�..";
			break;
		case 4:
			m_strDialogue = L"�˷��帱���? \n\n ��.. ���� �ȱñ��ѵ�.\n ����?";
			m_choose = 2;
			break;
		case 5:
			if (m_choosing == 1)
			{
				m_strDialogue = L"�׷� ��¿ �� ����!";
			}
			else
			{
				m_strDialogue = L"�ñ��ϴٸ� �����̶� ������ �����ּ���! \n������ ������ Ÿ������ ���ְŵ��!";
				
			}
			m_choose = 0;
			break;
		default:
			if (m_choosing == 1)
			{
				
			}
			else
			{
				changeTalkTopic=1;
			}
			m_choosing = 1;
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
			m_strDialogue = L"�ȳ��ϼ���!";
			break;
		case 2:
			m_strDialogue = L"������ ���̰� ���� ����� ���� �λ��ؾ��Ѵٰ� �߰ŵ��!";
			break;
		case 3:
			m_strDialogue = L"��.. ��! ���� ����ִ� ��о�⸦ �ϳ� �˰��ִµ�..";
			break;
		case 4:
			m_strDialogue = L"�˷��帱���? \n\n ���ܰ� ������ �ǳٴ�. \n ���� ���ɾ���.";
			m_choose = 2;
			break;
		case 5:
			if (m_choosing == 1)
			{
				if (GAME->IsItemInvenItem(L"����") && GAME->IsItemInvenItem(L"����"))
				{
					m_strDialogue = L"�� ���ƿ�! �˷��帱�Կ�.";
					GAME->EraseInvenItem(L"����");
					GAME->EraseInvenItem(L"����");
				}
				else
				{
					m_strDialogue = L"�峭ġ�� ������!";
					m_choosing = 2;
				}
			}
			else
			{
				m_strDialogue = L"�׷� ��¿ �� ����!";
			}
			m_choose = 0;

	
			break;
		case 6:
			if (m_choosing == 1)
			{
				m_strDialogue = L"�̰��� ���� ��û���� ū �����̾��ٰ� �ؿ�.";
			}
			else
			{
				CAMERA->ZoomInOut(2, 1);
				m_strDialogue = L"";
				GAME->SetTalk(false);
				talk = 0;
				DELETEOBJECT(pTalkBox);
				break;
			}
			m_choosing = 1;

			break;
		case 7:
			m_strDialogue = L"�׷��� �������簡 ��ٷӰ� �迭�Ǿ��־�, ����� �Ҷ� ���� �����Ǿ����.";
			break;
		case 8:
			m_strDialogue = L"�׵� �׷���, �� ������ ����� ���� �ܿ� 2�������ۿ� �ð��� �־����� �ʾҰŵ��!";
			break;
		case 9:
			m_strDialogue = L"�� ������� ���� ������� ��� �ٸ� ���� �ϰ� �Ǿ��ٰ� �ؿ�.";
			break;
		case 10:
			m_strDialogue = L"�̰� ����ε�, ��¼�� ������ ��� �Ŀ� ������ �ٸ� ����� �� �� ���� �־��!";
			break;
		case 11:
			m_strDialogue = L"���� ������ ���� �ʹٰ��?";
			break;
		case 12:
			m_strDialogue = L"��.. ���� �ƴ°�, ���� ������ ������ �����⿡ ���� 20500���� �����ؾ� �Ѵ��.";
			break;
		case 13:
			m_strDialogue = L"Ư���� �Ⱓ���� 10500���� �����Ѵٳ� ����.";
			break;
		default:
			CAMERA->ZoomInOut(2, 1);
			m_strDialogue = L"";
			changeTalkTopic++;
			GAME->SetTalk(false);
			talk = 0;
			DELETEOBJECT(pTalkBox);
			changeTalkTopic=2;
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
			m_strDialogue = L"�ȳ��ϼ���!";
			break;
		case 2:
			m_strDialogue = L"��� �̾߱⸦ �ٽ� �ѹ� �ص帱���? \n\n ��! \n �ƴ� �ƾ�.";
			m_choose = 2;
			break;
		case 3 :
			if (m_choosing == 1)
			{
				m_strDialogue = L"�̰��� ���� ��û���� ū �����̾��ٰ� �ؿ�.";
			}
			else
			{
				CAMERA->ZoomInOut(2, 1);
				m_strDialogue = L"";
				GAME->SetTalk(false);
				talk = 0;
				DELETEOBJECT(pTalkBox);
				break;
			}
			m_choosing = 1;
			m_choose = 0;
			break;
		case 4:
			m_strDialogue = L"�̰��� ���� ��û���� ū �����̾��ٰ� �ؿ�.";
			break;
		case 5:
			m_strDialogue = L"�׷��� �������簡 ��ٷӰ� �迭�Ǿ��־�, ����� �Ҷ� ���� �����Ǿ����.";
			break;
		case 6:
			m_strDialogue = L"�׵� �׷���, �� ������ ����� ���� �ܿ� 2�������ۿ� �ð��� �־����� �ʾҰŵ��!";
			break;
		case 7:
			m_strDialogue = L"�� ������� ���� ������� ��� �ٸ� ���� �ϰ� �Ǿ��ٰ� �ؿ�.";
			break;
		case 8:
			m_strDialogue = L"�̰� ����ε�, ��¼�� ������ ��� �Ŀ� ������ �ٸ� ����� �� �� ���� �־��!";
			break;
		case 9:
			m_strDialogue = L"���� ������ ���� �ʹٰ��?";
			break;
		case 10:
			m_strDialogue = L"��.. ���� �ƴ°�, ���� ������ ������ �����⿡ ���� 20500���� �����ؾ� �Ѵ��.";
			break;
		case 11:
			m_strDialogue = L"Ư���� �Ⱓ���� 10500���� �����Ѵٳ� ����.";
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
