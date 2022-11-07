#include "framework.h"
#include "CSceneForest.h"

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

CSceneForest::CSceneForest()
{
	pPlayer = nullptr;
	m_pImage = nullptr;
}

CSceneForest::~CSceneForest()
{
}

void CSceneForest::Init()
{
	pPlayer = new CPlayer();
	pPlayer->SetPos(200, WINSIZEY * 0.5f);
	AddGameObject(pPlayer);

	CSlug* pSlug = new CSlug();
	pSlug->SetPos(300, WINSIZEY * 0.5f - 10);
	AddGameObject(pSlug);

	CCameraController* pCamController = new CCameraController;
	AddGameObject(pCamController);



}

void CSceneForest::Enter()
{
	//백그라운드 이미지 (루프) 클래스 구현 

	//pLoad_BGM = RESOURCE->FindSound(L"Panselo");
	//SOUND->Play(pLoad_BGM, 1, true);

	m_pImage = RESOURCE->LoadImg(L"Forest_Back", L"Image\\Forest_Back.png");
	LoadBackground(m_pImage);

	m_pImage = RESOURCE->LoadImg(L"Forest_Middle", L"Image\\Forest_Middle.png");
	LoadMiddleground(m_pImage);

	//m_pVillageImage = RESOURCE->LoadImg(L"Cloud", L"Image\\Cloud.png");
	//CImageObject* pVillage2 = new CImageObject;
	//pVillage2->SetSpeed(1);
	//pVillage2->SetImage(m_pVillageImage);
	//AddGameObject(pVillage2);

	m_pImage = RESOURCE->LoadImg(L"Forest", L"Image\\Forest.png");
	CImageObject* pForest = new CImageObject;
	pForest->SetImage(m_pImage);
	AddGameObject(pForest);

	CAMERA->SetMapSize(Vector(m_pImage->GetWidth(), m_pImage->GetHeight()));
	CAMERA->ZoomInOut(2);
	CAMERA->SetTargetObj(pPlayer);

	CAMERA->FadeIn(0.25f);
	LoadTile(GETPATH + L"Tile\\Forest.tile");
}

void CSceneForest::Update()
{
	if (BUTTONDOWN(VK_ESCAPE))
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Title, 0.25f);
	}

	if (BUTTONDOWN(VK_F1))
	{
		CSlug* pSlug = new CSlug();
		pSlug->SetPos(300, WINSIZEY * 0.5f);
		AddGameObject(pSlug);
	}
}

void CSceneForest::Render()
{
}

void CSceneForest::Exit()
{
}

void CSceneForest::Release()
{
}
