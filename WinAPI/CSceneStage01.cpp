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

	CCarol* pCarol = new CCarol(pPlayer);
	pCarol->SetPos(625, 489);
	AddGameObject(pCarol);

	CSoldier* pSoldier = new CSoldier(pPlayer);
	pSoldier->SetPos(1632, 489);
	AddGameObject(pSoldier);

	CEventMark* pMilestone = new CEventMark(pPlayer);
	pMilestone->SetPos(1457, 489);
	pMilestone->m_strSetDialogue = L"평범한 표지판이다.";
	AddGameObject(pMilestone);

	//CBigBox* pBigBox = new CBigBox;
	//pBigBox->SetPos(420, 488);
	//AddGameObject(pBigBox);

	CBigBox* pBigBox2 = new CBigBox;
	pBigBox2->SetPos(425, 410);
	AddGameObject(pBigBox2);

	CBigBox* pBigBox3 = new CBigBox;
	pBigBox3->SetPos(772, 363);
	AddGameObject(pBigBox3);

	CBigBox* pBigBox4 = new CBigBox;
	pBigBox4->SetPos(109, 362);
	AddGameObject(pBigBox4);

	CBox* pBox = new CBox;
	pBox->SetPos(811, 363);
	AddGameObject(pBox);

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
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Title, 0.25f);
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
}

void CSceneStage01::Release()
{
}
