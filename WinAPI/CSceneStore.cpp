#include "framework.h"
#include "CSceneStore.h"

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
#include "CCarol.h"
#include "CLisa.h"
#include "CBuyEvent.h"
#include "CEventMark.h"
#include "CBigBox.h"

CSceneStore::CSceneStore()
{
	pPlayer = nullptr;
	m_pImage = nullptr;
	
}

CSceneStore::~CSceneStore()
{
}

void CSceneStore::Init()
{
	pPlayer = new CPlayer();
	AddGameObject(pPlayer);

	m_pImage = RESOURCE->LoadImg(L"Panselo_Back", L"Image\\Panselo_Back.png");
	LoadBackground(m_pImage);

	m_pImage = RESOURCE->LoadImg(L"Panselo_Middle", L"Image\\Panselo_Middle.png");
	LoadMiddleground(m_pImage);

	m_pImage = RESOURCE->LoadImg(L"Cloud", L"Image\\Cloud.png");
	LoadCloud(m_pImage);

	m_pImage = RESOURCE->LoadImg(L"Store", L"Image\\Store.png");
	CImageObject* pForest = new CImageObject;
	pForest->SetImage(m_pImage);
	AddGameObject(pForest);

	CDoor* pDoor = new CDoor;
	pDoor->SetPos(323, 400);
	pDoor->SetScene(GroupScene::Stage01);
	pDoor->SetImage(false);
	pDoor->SetPlayerStartPos(Vector(845, 488));
	pDoor->SetPlayerStartDir(pPlayer->GetDir());
	AddGameObject(pDoor);


	CBigBox* pBigBox = new CBigBox;
	pBigBox->SetPos(261, 310);
	AddGameObject(pBigBox);



	CLisa* pLisa = new CLisa(pPlayer);
	pLisa->SetPos(385, 400);
	AddGameObject(pLisa);

	CBuyEvent* pEgg = new CBuyEvent(pPlayer);
	pEgg->item = GAME->FindItem(L"페로 알");
	pEgg->SetPos(279, 390);
	AddGameObject(pEgg);

	CBuyEvent* pMilk = new CBuyEvent(pPlayer);
	pMilk->item = GAME->FindItem(L"우유");
	pMilk->SetPos(207, 390);
	AddGameObject(pMilk);

	CEventMark* pCake = new CEventMark(pPlayer);
	pCake->SetPos(243, 390);
	pCake->m_strSetDialogue = L"딸기케이크는 다 팔리고 없다.";
	AddGameObject(pCake);

}

void CSceneStore::Enter()
{
	CAMERA->FadeIn(0.25f);

	//pLoad_BGM = RESOURCE->FindSound(L"Panselo");
	//SOUND->Play(pLoad_BGM, 1, true);

	CAMERA->SetMapSize(Vector(m_pImage->GetWidth(), m_pImage->GetHeight()));
	CAMERA->ZoomInOut(3);
	
	CAMERA->SetTargetObj(pPlayer);

	pPlayer->SetPos(GAME->GetPlayerStartPos());
	pPlayer->SetDir(GAME->GetPlayerStartDir());
	pPlayer->SetGravity(1);
	pPlayer->SetPlatform(0);
	pPlayer->SetGround(0);

	CAMERA->FadeIn(0.25f);
	LoadTile(GETPATH + L"Tile\\Store.tile");
}

void CSceneStore::Update()
{
	if (BUTTONDOWN(VK_ESCAPE))
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Title, 0.25f);
	}

	if (BUTTONDOWN('I'))
	{
		GAME->SetCurScene(GroupScene::Store);
		GAME->SetPlayerStartPos(pPlayer->GetPos());
		CHANGESCENE(GroupScene::Inventory);
	}

}

void CSceneStore::Render()
{
	RENDER->Image(m_pDoor, 305, 380, 305 + m_pDoor->GetWidth(), 380 + m_pDoor->GetHeight());
}

void CSceneStore::Exit()
{
}

void CSceneStore::Release()
{
}
