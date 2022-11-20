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
#include "CCarol.h"
#include "CEventMark.h"
#include "CSoldier.h"
#include "CWarp.h"
#include "CBigBox.h"
#include "CBox.h"
#include "CCoin.h"
#include "CNana.h"
#include "CMarble.h"
#include "CPillarDoor.h"
#include "CFrontImage.h"
#include "CGhost.h"
#include "CImageEvent.h"
#include "CGrandma.h"
#include "CSoldier2.h"
#include "CBoy.h"
#include "CSound.h"
#include "CThief.h"

CSceneStage01::CSceneStage01()
{
	pPlayer = nullptr;
	m_pVillageImage = nullptr;
	pBox = nullptr;
	
}

CSceneStage01::~CSceneStage01()
{
}

void CSceneStage01::Init()
{


	pPlayer = new CPlayer();
	AddGameObject(pPlayer);


	CWarp* pFieldDoor = new CWarp;
	pFieldDoor->SetPos(1793, 489);
	pFieldDoor->SetScale(20, 150);
	pFieldDoor->SetScene(GroupScene::Field);
	pFieldDoor->SetPlayerStartPos(Vector(32, 488));
	pFieldDoor->SetPlayerStartDir(Vector(1, 0));
	AddGameObject(pFieldDoor);

	CDoor* pGymDoor = new CDoor;
	pGymDoor->SetPos(320, 489);
	pGymDoor->SetScene(GroupScene::Gym);
	pGymDoor->SetPlayerStartPos(Vector (18, 415));
	pGymDoor->SetPlayerStartDir(Vector(1, 0));
	AddGameObject(pGymDoor);

	CDoor* pStoreDoor = new CDoor;
	pStoreDoor->SetPos(845, 489);
	pStoreDoor->SetScene(GroupScene::Store);
	pStoreDoor->SetPlayerStartPos(Vector(323, 398));
	pStoreDoor->SetPlayerStartDir(pPlayer->GetDir());
	AddGameObject(pStoreDoor);

	CDoor* pGailRoomDoor = new CDoor;
	pGailRoomDoor->SetPos(1300, 489);
	pGailRoomDoor->SetScene(GroupScene::GailRoom);
	pGailRoomDoor->SetPlayerStartPos(Vector(306, 398));
	pGailRoomDoor->SetPlayerStartDir(pPlayer->GetDir());
	AddGameObject(pGailRoomDoor);


	CBigBox* pBigBox2 = new CBigBox;
	pBigBox2->SetPos(425, 410);
	AddGameObject(pBigBox2);

	CBigBox* pBigBox3 = new CBigBox;
	pBigBox3->SetPos(772, 363);
	AddGameObject(pBigBox3);

	CBigBox* pBigBox4 = new CBigBox;
	pBigBox4->SetPos(109, 362);
	AddGameObject(pBigBox4);

	pBox = new CBox;
	pBox->SetPos(811, 363);
	AddGameObject(pBox);

	CCarol* pCarol = new CCarol(pPlayer);
	pCarol->SetPos(625, 489);
	AddGameObject(pCarol);

	CNana* pNana = new CNana(pPlayer);
	pNana->SetPos(842, 382);
	AddGameObject(pNana);

	CSoldier* pSoldier = new CSoldier(pPlayer);
	pSoldier->SetPos(1632, 489);
	AddGameObject(pSoldier);

	CEventMark* pMilestone = new CEventMark(pPlayer);
	pMilestone->SetPos(1457, 489);
	pMilestone->m_strSetDialogue = L"´õºñ½£ ->";
	AddGameObject(pMilestone);

	CEventMark* pStore = new CEventMark(pPlayer);
	pStore->SetPos(900, 489);
	pStore->m_strSetDialogue = L"- ÆÇ¼¿·Î»óÁ¡ -";
	AddGameObject(pStore);

	//CBigBox* pBigBox = new CBigBox;
	//pBigBox->SetPos(420, 488);
	//AddGameObject(pBigBox);


	CCoin* pCoin = new CCoin;
	pCoin->SetPos(1165, 434);
	pCoin->SetDir(Vector(1, 0));
	pCoin->SetPrice(10);
	AddGameObject(pCoin);

	CMarble* pMarble = new CMarble;
	pMarble->dir = L"Left";
	pMarble->SetPos(1665, 421);
	AddGameObject(pMarble);

	CPillarDoor* pPillarDoor = new CPillarDoor;
	pPillarDoor->SetPos(1727,470);
	pPillarDoor->pMarble = pMarble;
	AddGameObject(pPillarDoor);
	
	CGrandma* pGrandma = new CGrandma(pPlayer);
	pGrandma->SetPos(728, 489);
	AddGameObject(pGrandma);

	CSoldier2* pSoldier2 = new CSoldier2(pPlayer);
	pSoldier2->SetPos(1153, 489);
	AddGameObject(pSoldier2);

	CBoy* pBoy = new CBoy(pPlayer);
	pBoy->SetPos(190, 310);
	AddGameObject(pBoy);

	CThief* pThief = new CThief(pPlayer);
	pThief->SetPos(1507, 489);
	AddGameObject(pThief);


}

void CSceneStage01::Enter()
{
	pLoad_BGM = RESOURCE->FindSound(L"DubbiForest");
	SOUND->Stop(pLoad_BGM);


	pLoad_BGM = RESOURCE->FindSound(L"Panselo");

	if (!(pLoad_BGM->IsPlaying()))
	{
		SOUND->Play(pLoad_BGM, 1, true);
	}
	else if (SOUND->GetVolume(pLoad_BGM) != 1);
	{
		SOUND->SetVolume(pLoad_BGM, 1);
	}

	pBox->SetPos(811, 380);
	pBox->SetPlatform(0);
	pBox->SetGround(0);

	if (GAME->mainQuest == MainQuest::VisitStore)
	{
		CImageEvent* pImageEvent = new CImageEvent(pPlayer);
		pImageEvent->SetPos(1099, 489);
		pImageEvent->pEventImage = RESOURCE->LoadImg(L"Board", L"Image\\Board.png");
		AddGameObject(pImageEvent);
	}

	

	m_pVillageImage = RESOURCE->LoadImg(L"Panselo_Back", L"Image\\Panselo_Back.png");
	LoadBackground(m_pVillageImage);

	m_pVillageImage = RESOURCE->LoadImg(L"Panselo_Middle", L"Image\\Panselo_Middle.png");
	LoadMiddleground(m_pVillageImage);

	m_pVillageImage = RESOURCE->LoadImg(L"Cloud", L"Image\\Cloud.png");
	LoadCloud(m_pVillageImage);

	m_pVillageImage = RESOURCE->LoadImg(L"Panselo", L"Image\\Panselo.png");
	CImageObject* pVillage = new CImageObject;
	pVillage->SetImage(m_pVillageImage);
	AddGameObject(pVillage);

	m_pVillageImage = RESOURCE->LoadImg(L"Panselo_Front", L"Image\\Panselo_Front.png");
	CFrontImage* pVillage2 = new CFrontImage;
	pVillage2->SetImage(m_pVillageImage);
	AddGameObject(pVillage2);

	pPlayer->SetPos(GAME->GetPlayerStartPos());
	pPlayer->SetDir(GAME->GetPlayerStartDir());
	pPlayer->SetGravity(1);
	pPlayer->SetPlatform(0);
	pPlayer->SetGround(0);

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
		GAME->SetCurScene(GroupScene::Stage01);
		GAME->SetPlayerStartPos(pPlayer->GetPos());
		CHANGESCENE(GroupScene::SetUp);
	}

	if (BUTTONDOWN('I'))
	{
		GAME->SetCurScene(GroupScene::Stage01);
		GAME->SetPlayerStartPos(pPlayer->GetPos());
		CHANGESCENE(GroupScene::Inventory);
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
	//SOUND->Stop(pLoad_BGM);
}

void CSceneStage01::Release()
{
}
