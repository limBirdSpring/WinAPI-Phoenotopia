#include "framework.h"
#include "CSceneStage01.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"
#include "CPathManager.h"
#include "CGameManager.h"

#include "CPlayer.h"
#include "CSlug.h"
#include "CCameraController.h"
#include "CButton.h"
#include "CPanel.h"
#include "CResourceManager.h"
#include "CImage.h"
#include "CImageObject.h"
#include "CSoundManager.h"
#include "CDoor.h"
#include "CUIManager.h"
#include "CButton.h"

CSceneStage01::CSceneStage01()
{
	pPlayer = nullptr;
	m_pVillageImage = nullptr;
}

CSceneStage01::~CSceneStage01()
{
}

void CSceneStage01::Init()
{
	pPlayer = new CPlayer();
	AddGameObject(pPlayer);

	CSlug* pSlug = new CSlug();
	pSlug->SetPos(300, WINSIZEY * 0.5f-10);
	AddGameObject(pSlug);

	CButton* pButton = new CButton;
	pButton->SetPos(500, 500);
	pButton->SetScale(100, 100);
	AddGameObject(pButton);

	CDoor* pDoor = new CDoor;
	pDoor->SetPos(320, 489);
	pDoor->SetScene(GroupScene::GailRoom);
	pDoor->SetPlayerStartPos(Vector (306, 272));
	AddGameObject(pDoor);
}

void CSceneStage01::Enter()
{
	//백그라운드 이미지 (루프) 클래스 구현 

	//pLoad_BGM = RESOURCE->FindSound(L"Panselo");
	//SOUND->Play(pLoad_BGM, 1, true);

	m_pVillageImage = RESOURCE->LoadImg(L"Panselo_Back", L"Image\\Panselo_Back.png");
	LoadBackground(m_pVillageImage);

	m_pVillageImage = RESOURCE->LoadImg(L"Panselo_Middle", L"Image\\Panselo_Middle.png");
	LoadMiddleground(m_pVillageImage);

	//m_pVillageImage = RESOURCE->LoadImg(L"Cloud", L"Image\\Cloud.png");
	//CImageObject* pVillage2 = new CImageObject;
	//pVillage2->SetSpeed(1);
	//pVillage2->SetImage(m_pVillageImage);
	//AddGameObject(pVillage2);

	m_pVillageImage = RESOURCE->LoadImg(L"Panselo", L"Image\\Panselo.png");
	CImageObject* pVillage = new CImageObject;
	pVillage->SetImage(m_pVillageImage);
	AddGameObject(pVillage);

	pPlayer->SetPos(GAME->GetPlayerStartPos());

	CAMERA->SetMapSize(Vector(m_pVillageImage->GetWidth(), m_pVillageImage->GetHeight()));
	CAMERA->ZoomInOut(2);
	CAMERA->SetTargetObj(pPlayer);

	
	CAMERA->FadeIn(0.25f);
	LoadTile(GETPATH + L"Tile\\Stage01.tile");
}

void CSceneStage01::Update()
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

	if (BUTTONDOWN(VK_F2))
	{
		DELAYCHANGESCENE(GroupScene::Forest, 0.25f);
	}

	if (BUTTONDOWN(VK_F3))
	{
		CAMERA->ZoomInOut(2,3);
	}
}

void CSceneStage01::Render()
{
}

void CSceneStage01::Exit()
{
}

void CSceneStage01::Release()
{
}
