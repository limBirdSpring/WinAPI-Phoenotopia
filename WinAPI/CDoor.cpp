#include "framework.h"
#include "CDoor.h"
#include "CCollider.h"
#include "CCollisionManager.h"
#include "CResourceManager.h"
#include "CAnimation.h"
#include "CInputManager.h"
#include "CEventManager.h"
#include "CGameManager.h"
#include "CCameraManager.h"

CDoor::CDoor()
{
	m_pImage = nullptr;
	m_pAnimator = nullptr;
	haveImage = true;
	isOpen = false;

	m_strName = L"문";
	m_vecPlayerStartPos = Vector(0,0);
	m_vecPlayerStartDir = Vector(0, 0);
	m_pScene = GroupScene::Title;
	m_vecScale = Vector(30, 30);
}

CDoor::~CDoor()
{
}

void CDoor::Init()
{
	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 1, m_vecScale.y - 1), Vector(0, 0));

	if (haveImage == true)
	{
		m_pImage = RESOURCE->LoadImg(L"Door", L"Image\\Door.png");

		m_pAnimator = new CAnimator;
		m_pAnimator->CreateAnimation(L"Door", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.1, 1, false);
		m_pAnimator->CreateAnimation(L"Door_Opened", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.1, 5, false);
		m_pAnimator->CreateAnimation(L"Door_Closed", m_pImage, Vector(600, 0), Vector(100, 100), Vector(-150, 0), 0.1, 5, false);

		m_pAnimator->Play(L"Door");
		AddComponent(m_pAnimator);
	}
	
}

void CDoor::Update()
{
}

void CDoor::Render()
{
}

void CDoor::Release()
{
}

void CDoor::OnCollisionEnter(CCollider* pOtherCollider)
{
}

void CDoor::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		if (haveImage == true)
		{
			if (BUTTONDOWN('X'))
			{
				if (!isOpen)
				{
					m_pAnimator->Play(L"Door_Opened");
					isOpen = true;
				}
				else
				{
					m_pAnimator->Play(L"Door_Closed");
					isOpen = false;
				}
			}
			if (BUTTONDOWN(VK_UP) && isOpen)
			{
				GAME->SetPlayerStartPos(m_vecPlayerStartPos);
				GAME->SetPlayerStartDir(m_vecPlayerStartDir);
				CAMERA->FadeOut(0.25f);
				DELAYCHANGESCENE(m_pScene, 0.25f);

			}
		}
		else
		{
			if (BUTTONDOWN(VK_UP))
			{
				GAME->SetPlayerStartPos(m_vecPlayerStartPos);
				GAME->SetPlayerStartDir(m_vecPlayerStartDir);
				CAMERA->FadeOut(0.25f);
				DELAYCHANGESCENE(m_pScene, 0.25f);

			}
		}
	}
}

void CDoor::OnCollisionExit(CCollider* pOtherCollider)
{
}

void CDoor::AnimatorUpdate()
{
}
