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
#include "CWarp.h"
#include "CTeacher.h"

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
	AddGameObject(pDoor);

	CTeacher* pTeacher = new CTeacher;
	pTeacher->SetPos(162, 417);
	AddGameObject(pTeacher);


	CSlug* pSlug = new CSlug();
	pSlug->SetPos(370, 452);
	AddGameObject(pSlug);


	CEventMark* pClothes = new CEventMark;
	pClothes->SetPos(171, 272);
	pClothes->SetScale(50, 50);
	pClothes->m_strSetDialogue = L"�ʱ��ڿ� �±ǵ� ������ ����ִ� �繰��.";
	AddGameObject(pClothes);

}

void CSceneGym::Enter()
{
	CAMERA->FadeIn(0.25f);

	//pLoad_BGM = RESOURCE->FindSound(L"Panselo");
	//SOUND->Play(pLoad_BGM, 1, true);


	CAMERA->SetMapSize(Vector(m_pImage->GetWidth(), m_pImage->GetHeight()));
	CAMERA->ZoomInOut(2);
	CAMERA->SetTargetObj(pPlayer);

	pPlayer->SetPos(GAME->GetPlayerStartPos());
	pPlayer->SetGravity(1);
	pPlayer->SetGround(0);

	CAMERA->FadeIn(0.25f);
	LoadTile(GETPATH + L"Tile\\Gym.tile");
}

void CSceneGym::Update()
{
	if (BUTTONDOWN(VK_ESCAPE))
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Title, 0.25f);
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
		GAME->PushBackInvenItem(L"������ �޴ٸ�");
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