#include "framework.h"
#include "CSceneGym.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"
#include "CPathManager.h"

#include "CPlayer.h"
#include "CPinkSlug.h"
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
#include "CWarp.h"
#include "CTeacher.h"
#include "CStudent.h"

CSceneGym::CSceneGym()
{
	pPlayer = nullptr;
	m_pImage = nullptr;
}

CSceneGym::~CSceneGym()
{
}

void CSceneGym::Init()
{
	pPlayer = new CPlayer();
	AddGameObject(pPlayer);

	m_pImage = RESOURCE->LoadImg(L"Panselo_Back", L"Image\\Panselo_Back.png");
	LoadBackground(m_pImage);

	m_pImage = RESOURCE->LoadImg(L"Panselo_Middle", L"Image\\Panselo_Middle.png");
	LoadMiddleground(m_pImage);

	m_pImage = RESOURCE->LoadImg(L"Gym", L"Image\\Gym.png");
	CImageObject* pForest = new CImageObject;
	pForest->SetImage(m_pImage);
	AddGameObject(pForest);

	CWarp* pDoor = new CWarp;
	pDoor->SetPos(0, 359);
	pDoor->SetScale(10, 150);
	pDoor->SetScene(GroupScene::Stage01);
	pDoor->SetPlayerStartPos(Vector(320, 488));
	pDoor->SetPlayerStartDir(pPlayer->GetDir());
	AddGameObject(pDoor);



	CStudent* pStudent = new CStudent(pPlayer);
	pStudent->SetPos(572, 453);
	AddGameObject(pStudent);


	CPinkSlug* pPinkSlug = new CPinkSlug();
	pPinkSlug->SetPos(370, 452);
	AddGameObject(pPinkSlug);


	CEventMark* pClothes = new CEventMark(pPlayer);
	pClothes->SetPos(171, 272);
	pClothes->SetScale(50, 50);
	pClothes->m_strSetDialogue = L"초급자용 태권도 도복이 들어있는 사물함.";
	AddGameObject(pClothes);

}

void CSceneGym::Enter()
{
	if (GAME->mainQuest == MainQuest::FindBoard && isTeacher == false)
	{
		isTeacher = true;
		CTeacher* pTeacher = new CTeacher(pPlayer);
		pTeacher->SetPos(162, 417);
		AddGameObject(pTeacher);
	}

	pLoad_BGM = RESOURCE->FindSound(L"Panselo");
	SOUND->Stop(pLoad_BGM);

	pLoad_BGM = RESOURCE->FindSound(L"Gym");

	if (!(pLoad_BGM->IsPlaying()))
	{
		SOUND->Play(pLoad_BGM, 1, true);
	}

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
	LoadTile(GETPATH + L"Tile\\Gym.tile");
}

void CSceneGym::Update()
{
	if (BUTTONDOWN(VK_ESCAPE))
	{
		GAME->SetCurScene(GroupScene::Gym);
		GAME->SetPlayerStartPos(pPlayer->GetPos());
		CHANGESCENE(GroupScene::SetUp);
	}

	if (BUTTONDOWN('I'))
	{
		GAME->SetCurScene(GroupScene::Gym);
		GAME->SetPlayerStartPos(pPlayer->GetPos());
		CHANGESCENE(GroupScene::Inventory);
	}

	if (BUTTONDOWN('J'))
	{
		GAME->PushBackInvenItem(GAME->m_vItem[0]);
		GAME->PushBackInvenItem(GAME->m_vItem[1]);
		GAME->PushBackInvenItem(L"개구리 뒷다리");
	}
}

void CSceneGym::Render()
{
}

void CSceneGym::Exit()
{

}

void CSceneGym::Release()
{
}
