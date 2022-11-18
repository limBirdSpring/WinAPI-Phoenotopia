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
	if (pOtherCollider->GetObjName() == L"플레이어")
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
			m_strDialogue = L"안녕하세요!";
			break;
		case 2:
			m_strDialogue = L"엄마가 나이가 많은 사람을 보면 인사해야한다고 했거든요!";
			break;
		case 3:
			m_strDialogue = L"음.. 아! 제가 재미있는 비밀얘기를 하나 알고있는데..";
			break;
		case 4:
			m_strDialogue = L"알려드릴까요? \n\n 음.. 별로 안궁금한데.\n 뭔데?";
			m_choose = 2;
			break;
		case 5:
			if (m_choosing == 1)
			{
				m_strDialogue = L"그럼 어쩔 수 없죠!";
			}
			else
			{
				m_strDialogue = L"궁금하다면 벌꿀이랑 우유를 갖다주세요! \n우유에 벌꿀을 타먹으면 맛있거든요!";
				
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
			m_strDialogue = L"안녕하세요!";
			break;
		case 2:
			m_strDialogue = L"엄마가 나이가 많은 사람을 보면 인사해야한다고 했거든요!";
			break;
		case 3:
			m_strDialogue = L"음.. 아! 제가 재미있는 비밀얘기를 하나 알고있는데..";
			break;
		case 4:
			m_strDialogue = L"알려드릴까요? \n\n 벌꿀과 우유를 건넨다. \n 별로 관심없어.";
			m_choose = 2;
			break;
		case 5:
			if (m_choosing == 1)
			{
				if (GAME->IsItemInvenItem(L"벌꿀") && GAME->IsItemInvenItem(L"우유"))
				{
					m_strDialogue = L"음 좋아요! 알려드릴게요.";
					GAME->EraseInvenItem(L"벌꿀");
					GAME->EraseInvenItem(L"우유");
				}
				else
				{
					m_strDialogue = L"장난치지 마세요!";
					m_choosing = 2;
				}
			}
			else
			{
				m_strDialogue = L"그럼 어쩔 수 없죠!";
			}
			m_choose = 0;

	
			break;
		case 6:
			if (m_choosing == 1)
			{
				m_strDialogue = L"이곳은 원래 엄청나게 큰 마을이었다고 해요.";
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
			m_strDialogue = L"그런데 건축자재가 까다롭게 배열되어있어, 재건을 할때 많이 생략되었대요.";
			break;
		case 8:
			m_strDialogue = L"그도 그럴게, 이 마을을 재건할 때는 겨우 2주정도밖에 시간이 주어지지 않았거든요!";
			break;
		case 9:
			m_strDialogue = L"그 충격으로 마을 사람들이 모두 다른 말을 하게 되었다고 해요.";
			break;
		case 10:
			m_strDialogue = L"이건 비밀인데, 어쩌면 누나도 재건 후에 완전히 다른 사람이 된 걸 수도 있어요!";
			break;
		case 11:
			m_strDialogue = L"원래 마을을 보고 싶다고요?";
			break;
		case 12:
			m_strDialogue = L"음.. 제가 아는건, 원래 마을로 가려면 수증기에 가서 20500원을 지불해야 한대요.";
			break;
		case 13:
			m_strDialogue = L"특정한 기간에는 10500으로 할인한다나 뭐라나.";
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
			m_strDialogue = L"안녕하세요!";
			break;
		case 2:
			m_strDialogue = L"비밀 이야기를 다시 한번 해드릴까요? \n\n 응! \n 아니 됐어.";
			m_choose = 2;
			break;
		case 3 :
			if (m_choosing == 1)
			{
				m_strDialogue = L"이곳은 원래 엄청나게 큰 마을이었다고 해요.";
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
			m_strDialogue = L"이곳은 원래 엄청나게 큰 마을이었다고 해요.";
			break;
		case 5:
			m_strDialogue = L"그런데 건축자재가 까다롭게 배열되어있어, 재건을 할때 많이 생략되었대요.";
			break;
		case 6:
			m_strDialogue = L"그도 그럴게, 이 마을을 재건할 때는 겨우 2주정도밖에 시간이 주어지지 않았거든요!";
			break;
		case 7:
			m_strDialogue = L"그 충격으로 마을 사람들이 모두 다른 말을 하게 되었다고 해요.";
			break;
		case 8:
			m_strDialogue = L"이건 비밀인데, 어쩌면 누나도 재건 후에 완전히 다른 사람이 된 걸 수도 있어요!";
			break;
		case 9:
			m_strDialogue = L"원래 마을을 보고 싶다고요?";
			break;
		case 10:
			m_strDialogue = L"음.. 제가 아는건, 원래 마을로 가려면 수증기에 가서 20500원을 지불해야 한대요.";
			break;
		case 11:
			m_strDialogue = L"특정한 기간에는 10500으로 할인한다나 뭐라나.";
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
