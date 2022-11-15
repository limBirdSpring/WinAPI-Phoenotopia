#include "framework.h"
#include "CStatue.h"

#include "CCollider.h"
#include "CGravity.h"
#include "CImage.h"
#include "CItem.h"
#include "CAnimator.h"
#include "CTalkBox.h"
#include "CPlayer.h"

CStatue::CStatue()
{
	m_vecScale = Vector(15, 15);
	isStatueOn = true;
	m_layer = Layer::Door;
	pTalkBox = nullptr;
	m_strDialogue = L"";
	talk = 0;
}

CStatue::~CStatue()
{

}

void CStatue::Init()
{
	m_pImage = RESOURCE->LoadImg(L"UI_!", L"Image\\UI_!.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"UI_!", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.1, 6);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 1, m_vecScale.y - 1), Vector(0, 0));
}

void CStatue::Update()
{
	if (talk > 0)
		pTalkBox->m_strDialogue = m_strDialogue;
}

void CStatue::Render()
{
}

void CStatue::Release()
{
}

void CStatue::OnCollisionEnter(CCollider* pOtherCollider)
{
	
}

void CStatue::OnCollisionStay(CCollider* pOtherCollider)
{
	m_pAnimator->Play(L"UI_!");
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		CPlayer* pPlayer = static_cast<CPlayer*>(pOtherCollider->GetOwner());

		
		if (BUTTONDOWN('X'))
		{
			if (GAME->GetTalk())
			{
				m_strDialogue = L"";
				GAME->SetTalk(false);
				DELETEOBJECT(pTalkBox);
				talk = 0;
			}
			else if (GAME->IsItemInvenItem(L"젬") == true && isStatueOn == true)
			{
				GAME->EraseInvenItem(L"젬");
				isStatueOn = false;
				GAME->SetTalk(true);

				pPlayer->m_behavior = Behavior::Talk;

				pTalkBox = new CTalkBox;
				pTalkBox->SetPos(this->GetPos());
				ADDOBJECT(pTalkBox);
				talk = 1;
				Talk();
			}
			else if (isStatueOn == true)
			{
				GAME->SetTalk(true);

				pPlayer->m_behavior = Behavior::Talk;
				pTalkBox = new CTalkBox;
				pTalkBox->SetPos(this->GetPos());
				ADDOBJECT(pTalkBox);
				talk = 2;
				Talk();
			}
			else
			{
				GAME->SetTalk(true);

				pPlayer->m_behavior = Behavior::Talk;
				pTalkBox = new CTalkBox;
				pTalkBox->SetPos(this->GetPos());

				ADDOBJECT(pTalkBox);
				talk = 3;
				Talk();
			}


		}
		
		

	}
}

void CStatue::OnCollisionExit(CCollider* pOtherCollider)
{
	m_pAnimator->Stop();
}

void CStatue::Talk()
{
	switch (talk)
	{
	case 1:
		m_strDialogue = L"젬을 끼웠다.";
		break;
	case 2:
		m_strDialogue = L"젬을 넣을 수 있는 홈이 있다.";
		break;
	case 3:
		m_strDialogue = L"이미 문이 열렸다.";
		break;
	}

}
