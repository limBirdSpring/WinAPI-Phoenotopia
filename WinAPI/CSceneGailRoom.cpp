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
#include "CEventMark.h"
#include "CStatue.h"
#include "CImageEvent.h"
#include "CFrontImage.h"
#include "CImageBox.h"
#include "CStartEvent.h"

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

	m_pImage = RESOURCE->LoadImg(L"Cloud", L"Image\\Cloud.png");

	m_pImage = RESOURCE->LoadImg(L"InDoor", L"Image\\InDoor.png");
	CFrontImage* pInDoor = new CFrontImage;
	pInDoor->SetImage(m_pImage);
	pInDoor->SetPos(289, 380);
	AddGameObject(pInDoor);
	LoadCloud(m_pImage);

	m_pImage = RESOURCE->LoadImg(L"GailRoom", L"Image\\GailRoom.png");
	CImageObject* pForest = new CImageObject;
	pForest->SetImage(m_pImage);
	AddGameObject(pForest);

	

	CDoor* pDoor = new CDoor;
	pDoor->SetPos(306, 400);
	pDoor->SetScene(GroupScene::Stage01);
	pDoor->SetImage(false);
	pDoor->SetPlayerStartPos(Vector(1300, 488));
	pDoor->SetPlayerStartDir(pPlayer->GetDir());
	AddGameObject(pDoor);

	CEventMark* pClothes = new CEventMark(pPlayer);
	pClothes->SetPos(334, 400);
	pClothes->m_strSetDialogue = L"도복이다. 맞다. 태권도학원 가야하는데..";
	AddGameObject(pClothes);

	CEventMark* pBed = new CEventMark(pPlayer);
	pBed->SetPos(377, 400);
	pBed->m_strSetDialogue = L"아직 잘 시간은 아니다.";
	AddGameObject(pBed);

	CImageEvent* pPhoto = new CImageEvent(pPlayer);
	pPhoto->SetPos(449, 400);
	pPhoto->pEventImage = RESOURCE->LoadImg(L"Photo", L"Image\\Photo.png");
	AddGameObject(pPhoto);


	CStartEvent* pStartEvent = new CStartEvent(pPlayer);
	AddGameObject(pStartEvent);

}

void CSceneGailRoom::Enter()
{
	pLoad_BGM = RESOURCE->FindSound(L"Panselo");

	if (pLoad_BGM->IsPlaying(), SOUND->GetVolume(pLoad_BGM) != 0.5);
	{
		SOUND->SetVolume(pLoad_BGM, 0.5);
	}

	GAME->SetUIRender(true);
	CAMERA->FadeIn(0.25f);


	
	CAMERA->SetMapSize(Vector(m_pImage->GetWidth(), m_pImage->GetHeight()));
	CAMERA->ZoomInOut(3);
	CAMERA->SetTargetPos(Vector(m_pImage->GetWidth() * 0.5, m_pImage->GetHeight()));

	pPlayer->SetPos(GAME->GetPlayerStartPos());
	pPlayer->SetDir(GAME->GetPlayerStartDir());
	pPlayer->SetGravity(1);
	pPlayer->SetPlatform(0);
	pPlayer->SetGround(0);

	CAMERA->FadeIn(0.25f);
	LoadTile(GETPATH + L"Tile\\GailRoom.tile");
}

void CSceneGailRoom::Update()
{



	if (BUTTONDOWN(VK_ESCAPE))
	{
		GAME->SetCurScene(GroupScene::GailRoom);
		GAME->SetPlayerStartPos(pPlayer->GetPos());
		CHANGESCENE(GroupScene::SetUp);
	}

	if (BUTTONDOWN('I'))
	{
		GAME->SetCurScene(GroupScene::GailRoom);
		GAME->SetPlayerStartPos(pPlayer->GetPos());
		CHANGESCENE(GroupScene::Inventory);
	}

	if (BUTTONDOWN('J'))
	{
		GAME->PushBackInvenItem(GAME->m_vItem[0]);
		GAME->PushBackInvenItem(GAME->m_vItem[1]);
		GAME->PushBackInvenItem(L"개구리 뒷다리");
		GAME->PushBackInvenItem(L"젬");
		GAME->PushBackInvenItem(L"도시락");
	}
}

void CSceneGailRoom::Render()
{
	
	RENDER->Text(L"기본조작 : 방향키   상호작용/말걸기 : X", 280, 217, 500, 244);
}

void CSceneGailRoom::Exit()
{
}

void CSceneGailRoom::Release()
{
}
