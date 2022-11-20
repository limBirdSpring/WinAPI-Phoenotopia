#include "framework.h"
#include "CSceneForest.h"

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
#include "CEventMark.h"
#include "CWarp.h"
#include "CTeacher.h"
#include "CItem.h"
#include "CBox.h"
#include "CBee.h"

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
	AddGameObject(pPlayer);

	m_pImage = RESOURCE->LoadImg(L"Forest_Back", L"Image\\Forest_Back.png");
	LoadBackground(m_pImage);

	m_pImage = RESOURCE->LoadImg(L"Forest_Middle", L"Image\\Forest_Middle.png");
	LoadMiddleground(m_pImage);

	m_pImage = RESOURCE->LoadImg(L"Cloud", L"Image\\Cloud.png");
	LoadCloud(m_pImage);

	m_pImage = RESOURCE->LoadImg(L"Forest", L"Image\\Forest.png");
	CImageObject* pForest = new CImageObject;
	pForest->SetImage(m_pImage);
	AddGameObject(pForest);

	CWarp* pDoor = new CWarp;
	pDoor->SetPos(0, 400);
	pDoor->SetScale(10, 1000);
	pDoor->SetScene(GroupScene::Field);
	pDoor->SetPlayerStartPos(Vector(1073, 488));
	pDoor->SetPlayerStartDir(Vector(-1, 0));
	AddGameObject(pDoor);

	CWarp* pDoor2 = new CWarp;
	pDoor2->SetPos(679, 259);
	pDoor2->SetScale(10, 400);
	pDoor2->SetScene(GroupScene::BossMap);
	pDoor2->SetPlayerStartPos(Vector(15, 488));
	pDoor2->SetPlayerStartDir(Vector(1, 0));
	AddGameObject(pDoor2);
	

	CItem* pZem = new CItem;
	pZem->SetPos(43, 237);
	pZem->SetItem(L"Áª");
	AddGameObject(pZem);

	pBox = new CBox;
	pBox->SetPos(116, 765);
	AddGameObject(pBox);

	CSlug* pSlug = new CSlug();
	pSlug->SetPos(370, 452);
	AddGameObject(pSlug);


	m_vFrog.push_back(new CFrog);
	m_vFrog[0]->SetStartXToEndX(66, 676);
	m_vFrog[0]->SetPos(591, 730);
	AddGameObject(m_vFrog[0]);

	m_vFrog.push_back(new CFrog);
	m_vFrog[1]->SetStartXToEndX(66, 676);
	m_vFrog[1]->SetPos(494, 378);
	AddGameObject(m_vFrog[1]);

	m_vFrog.push_back(new CFrog);
	m_vFrog[2]->SetStartXToEndX(66, 676);
	m_vFrog[2]->SetPos(102, 393);
	AddGameObject(m_vFrog[2]);

	m_vBee.push_back(new CBee);
	m_vBee[0]->SetStartXToEndX(66, 676);
	m_vBee[0]->SetPos(151, 304);
	AddGameObject(m_vBee[0]);

	m_vBee.push_back(new CBee);
	m_vBee[1]->SetStartXToEndX(66, 676);
	m_vBee[1]->SetPos(335, 344);
	AddGameObject(m_vBee[1]);

	m_vBee.push_back(new CBee);
	m_vBee[2]->SetStartXToEndX(66, 676);
	m_vBee[2]->SetPos(626, 617);
	AddGameObject(m_vBee[2]);
}

void CSceneForest::Enter()
{
	CAMERA->FadeIn(0.25f);

	//pLoad_BGM = RESOURCE->FindSound(L"Panselo");
	//SOUND->Play(pLoad_BGM, 1, true);


	CAMERA->SetMapSize(Vector(m_pImage->GetWidth(), m_pImage->GetHeight()));
	CAMERA->ZoomInOut(2);
	CAMERA->SetTargetObj(pPlayer);

	if (pBox->GetPos().x < 60 || pBox->GetPos().x > 670)
	{
		pBox->SetPos(116, 765);
		pBox->SetGround(0);
		pBox->SetPlatform(0);
	}

	m_vBee[0]->SetPos(151, 304);
	m_vBee[1]->SetPos(335, 344);
	m_vBee[2]->SetPos(626, 617);

	m_vFrog[0]->SetPos(591, 780);
	m_vFrog[1]->SetPos(494, 385);
	m_vFrog[2]->SetPos(102, 546);



	pPlayer->SetPos(GAME->GetPlayerStartPos());
	pPlayer->SetDir(GAME->GetPlayerStartDir());
	pPlayer->SetGravity(1);
	pPlayer->SetGround(0);
	pPlayer->SetPlatform(0);

	CAMERA->FadeIn(0.25f);
	LoadTile(GETPATH + L"Tile\\Forest.tile");
}

void CSceneForest::Update()
{
	if (BUTTONDOWN(VK_ESCAPE))
	{
		GAME->SetCurScene(GroupScene::Forest);
		GAME->SetPlayerStartPos(pPlayer->GetPos());
		CHANGESCENE(GroupScene::SetUp);
	}

	if (BUTTONDOWN('I'))
	{
		GAME->SetCurScene(GroupScene::Forest);
		GAME->SetPlayerStartPos(pPlayer->GetPos());
		CHANGESCENE(GroupScene::Inventory);
	}

	if (GAME->GetHp() <= 0)
	{
		pLoad_BGM = RESOURCE->FindSound(L"DubbiForest");
		SOUND->Stop(pLoad_BGM);
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Dead, 1.f);
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
