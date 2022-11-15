#include "framework.h"
#include "CImageEvent.h"

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

CImageEvent::CImageEvent(CPlayer* player)
{
	pPlayer = player;
	m_vecScale = Vector(18, 32);
	pEventImage = nullptr;
	bIsImageRender = false;
}

CImageEvent::~CImageEvent()
{
}

void CImageEvent::Init()
{
	m_pImage = RESOURCE->LoadImg(L"UI_!", L"Image\\UI_!.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"UI_!", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.1, 6);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 0.1, m_vecScale.y - 0.1), Vector(0, 4));
}

void CImageEvent::Update()
{
}

void CImageEvent::Render()
{
	Vector pos = CAMERA->ScreenToWorldPoint(Vector(WINSIZEX * 0.5, WINSIZEY *0.5), false);

	if (bIsImageRender)
	{
		RENDER->Image(pEventImage, pos.x - pEventImage->GetWidth()*0.5, pos.y - pEventImage->GetHeight()*0.5, pos.x + pEventImage->GetWidth() * 0.5, pos.y + pEventImage->GetHeight() * 0.5);
	}
}

void CImageEvent::Release()
{
}

void CImageEvent::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		m_pAnimator->Play(L"UI_!");

		if (BUTTONDOWN('X'))
		{
			if (!bIsImageRender)
			{
				pPlayer->m_behavior = Behavior::Talk;
				GAME->SetTalk(true);
				bIsImageRender = true;
			}
			else
			{
				GAME->SetTalk(false);
				bIsImageRender = false;
			}
		}
	}
}

void CImageEvent::OnCollisionExit(CCollider* pOtherCollider)
{
	m_pAnimator->Stop();
}


