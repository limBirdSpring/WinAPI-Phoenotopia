#include "framework.h"
#include "CSceneStage01.h"

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
	pPlayer->SetPos(200, WINSIZEY * 0.5f);
	AddGameObject(pPlayer);

	CSlug* pSlug = new CSlug();
	pSlug->SetPos(300, WINSIZEY * 0.5f-10);
	AddGameObject(pSlug);

	CCameraController* pCamController = new CCameraController;
	AddGameObject(pCamController);



}

void CSceneStage01::Enter()
{
	//��׶��� �̹��� (����) Ŭ���� ���� 

	//pLoad_BGM = RESOURCE->FindSound(L"Panselo");
	//SOUND->Play(pLoad_BGM, 1, true);

	m_pVillageImage = RESOURCE->LoadImg(L"Panselo_Back", L"Image\\Panselo_Back.png");
	LoadBackground(m_pVillageImage);

	m_pVillageImage = RESOURCE->LoadImg(L"Panselo_Middle", L"Image\\Panselo_Middle.png");
	LoadMiddleground(m_pVillageImage);

	m_pVillageImage = RESOURCE->LoadImg(L"Panselo", L"Image\\Panselo.png");
	CImageObject* pVillage = new CImageObject;
	pVillage->SetImage(m_pVillageImage);
	AddGameObject(pVillage);

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
