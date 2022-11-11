#include "framework.h"
#include "CWarp.h"
#include "CCollider.h"
#include "CCollisionManager.h"
#include "CResourceManager.h"
#include "CAnimation.h"
#include "CInputManager.h"
#include "CEventManager.h"
#include "CGameManager.h"
#include "CCameraManager.h"

CWarp::CWarp()
{
	m_strName = L"워프";
	m_vecPlayerStartPos = Vector(0, 0);
	m_pScene = GroupScene::Title;
	m_vecScale = Vector(30, 30);
	m_layer = Layer::Door;

}

CWarp::~CWarp()
{
}

void CWarp::Init()
{
	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 1, m_vecScale.y - 1), Vector(0, 0));

}

void CWarp::Update()
{
}

void CWarp::Render()
{
}

void CWarp::Release()
{
}

void CWarp::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어")
	{

		GAME->SetPlayerStartPos(m_vecPlayerStartPos);
		GAME->SetPlayerStartDir(m_vecPlayerStartDir);
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(m_pScene, 0.25f);

	}
}

void CWarp::OnCollisionStay(CCollider* pOtherCollider)
{

}

void CWarp::OnCollisionExit(CCollider* pOtherCollider)
{
}

void CWarp::AnimatorUpdate()
{
}
