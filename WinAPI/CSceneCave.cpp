#include "framework.h"
#include "CSceneCave.h"

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
#include "CWarp.h"
#include "CEventMark.h"
#include "CStatue.h"
#include "CImageEvent.h"
#include "CFrontImage.h"
#include "CImageBox.h"
#include "CStartEvent.h"
#include "CMarble.h"
#include "CPillarDoor.h"
#include "CTreasure.h"

CSceneCave::CSceneCave()
{
	pPlayer = nullptr;
	m_pImage = nullptr;
}

CSceneCave::~CSceneCave()
{
}

void CSceneCave::Init()
{
	pPlayer = new CPlayer();
	AddGameObject(pPlayer);

	m_pImage = RESOURCE->LoadImg(L"Cave", L"Image\\Cave.png");
	CImageObject* pVillage = new CImageObject;
	pVillage->SetImage(m_pImage);
	AddGameObject(pVillage);

	m_pImage = RESOURCE->LoadImg(L"Cave_Front", L"Image\\Cave_Front.png");
	CFrontImage* pVillage2 = new CFrontImage;
	pVillage2->SetImage(m_pImage);
	AddGameObject(pVillage2);


	CWarp* pDoor = new CWarp;
	pDoor->SetPos(4, 500);
	pDoor->SetScale(10,200);
	pDoor->SetScene(GroupScene::Forest);
	pDoor->SetPlayerStartPos(Vector(625, 774));
	pDoor->SetPlayerStartDir(pPlayer->GetDir());
	AddGameObject(pDoor);

	CMarble* pMarble = new CMarble;
	pMarble->dir = L"Right";
	pMarble->SetPos(153, 220);
	AddGameObject(pMarble);

	CPillarDoor* pPillarDoor = new CPillarDoor;
	pPillarDoor->SetPos(413, 250);
	pPillarDoor->pMarble = pMarble;
	AddGameObject(pPillarDoor);

	CTreasure* pTreasure = new CTreasure;
	pTreasure->SetPos(455,265);
	AddGameObject(pTreasure);

}

void CSceneCave::Enter()
{
	pLoad_BGM = RESOURCE->FindSound(L"DubbiForest");

	if (pLoad_BGM->IsPlaying(), SOUND->GetVolume(pLoad_BGM) != 0.5);
	{
		SOUND->SetVolume(pLoad_BGM, 0.5);
	}

	CAMERA->FadeIn(0.25f);


	CAMERA->SetMapSize(Vector(m_pImage->GetWidth(), m_pImage->GetHeight()));
	CAMERA->ZoomInOut(3);
	CAMERA->SetTargetObj(pPlayer);

	pPlayer->SetPos(GAME->GetPlayerStartPos());
	pPlayer->SetDir(GAME->GetPlayerStartDir());
	pPlayer->SetGravity(1);
	pPlayer->SetPlatform(0);
	pPlayer->SetGround(0);

	CAMERA->FadeIn(0.25f);
	LoadTile(GETPATH + L"Tile\\Cave.tile");

	GAME->SetCurScene(GroupScene::Cave);
}

void CSceneCave::Update()
{



	if (BUTTONDOWN(VK_ESCAPE))
	{
		GAME->SetCurScene(GroupScene::Cave);
		GAME->SetPlayerStartPos(pPlayer->GetPos());
		CHANGESCENE(GroupScene::SetUp);
	}

	if (BUTTONDOWN('I'))
	{
		GAME->SetCurScene(GroupScene::Cave);
		GAME->SetPlayerStartPos(pPlayer->GetPos());
		CHANGESCENE(GroupScene::Inventory);
	}

}

void CSceneCave::Render()
{
}

void CSceneCave::Exit()
{
}

void CSceneCave::Release()
{
}
