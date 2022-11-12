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

	

	CItem* pZem = new CItem;
	pZem->SetPos(43, 237);
	pZem->SetItem(L"Áª");
	AddGameObject(pZem);

	CBox* pBox = new CBox;
	pBox->SetPos(116, 765);
	AddGameObject(pBox);

	CSlug* pSlug = new CSlug();
	pSlug->SetPos(370, 452);
	AddGameObject(pSlug);


}

void CSceneForest::Enter()
{
	CAMERA->FadeIn(0.25f);

	//pLoad_BGM = RESOURCE->FindSound(L"Panselo");
	//SOUND->Play(pLoad_BGM, 1, true);


	CAMERA->SetMapSize(Vector(m_pImage->GetWidth(), m_pImage->GetHeight()));
	CAMERA->ZoomInOut(2);
	CAMERA->SetTargetObj(pPlayer);

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
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Title, 0.25f);
	}

	if (BUTTONDOWN('I'))
	{
		GAME->SetCurScene(GroupScene::Field);
		GAME->SetPlayerStartPos(pPlayer->GetPos());
		CHANGESCENE(GroupScene::Inventory);
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
