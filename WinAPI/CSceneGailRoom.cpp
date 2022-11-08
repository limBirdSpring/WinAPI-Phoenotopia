#include "framework.h"
#include "CSceneGailRoom.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"
#include "CPathManager.h"

#include "CPlayer.h"
#include "CSlug.h"
#include "CCameraController.h"
#include "CButton.h"
#include "CPanel.h"
#include "CResourceManager.h"
#include "CImage.h"
#include "CImageObject.h"
#include "CSoundManager.h"
#include "CGameManager.h"
#include "CDoor.h"

CSceneGailRoom::CSceneGailRoom()
{
	pPlayer = nullptr;
	m_pImage = nullptr;
}

CSceneGailRoom::~CSceneGailRoom()
{
}

void CSceneGailRoom::Init()
{
	pPlayer = new CPlayer();
	AddGameObject(pPlayer);

	m_pImage = RESOURCE->LoadImg(L"Panselo_Back", L"Image\\Panselo_Back.png");
	LoadBackground(m_pImage);

	m_pImage = RESOURCE->LoadImg(L"Panselo_Middle", L"Image\\Panselo_Middle.png");
	LoadMiddleground(m_pImage);

	m_pImage = RESOURCE->LoadImg(L"GailRoom", L"Image\\GailRoom.png");
	CImageObject* pForest = new CImageObject;
	pForest->SetImage(m_pImage);
	AddGameObject(pForest);

	CDoor* pDoor = new CDoor;
	pDoor->SetPos(306, 278);
	pDoor->SetScene(GroupScene::Stage01);
	pDoor->SetImage(false);
	pDoor->SetPlayerStartPos(Vector(320, 488));
	AddGameObject(pDoor);
}

void CSceneGailRoom::Enter()
{
	CAMERA->FadeIn(0.25f);

	//pLoad_BGM = RESOURCE->FindSound(L"Panselo");
	//SOUND->Play(pLoad_BGM, 1, true);

	
	CAMERA->SetMapSize(Vector(m_pImage->GetWidth(), m_pImage->GetHeight()));
	CAMERA->ZoomInOut(3);
	CAMERA->SetTargetPos(Vector(m_pImage->GetWidth() * 0.5, m_pImage->GetHeight() * 0.5));

	pPlayer->SetPos(GAME->GetPlayerStartPos());

	CAMERA->FadeIn(0.25f);
	LoadTile(GETPATH + L"Tile\\GailRoom.tile");
}

void CSceneGailRoom::Update()
{
	if (BUTTONDOWN(VK_ESCAPE))
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Title, 0.25f);
	}

}

void CSceneGailRoom::Render()
{
}

void CSceneGailRoom::Exit()
{
}

void CSceneGailRoom::Release()
{
}
