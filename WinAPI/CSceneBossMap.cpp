#include "framework.h"
#include "CSceneBossMap.h"

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
#include "CItem.h"
#include "CBox.h"
#include "CTurtle.h"
#include "CFrog.h"
#include "CBee.h"

CSceneBossMap::CSceneBossMap()
{
	pPlayer = nullptr;
	m_pImage = nullptr;
}

CSceneBossMap::~CSceneBossMap()
{
}

void CSceneBossMap::Init()
{
	pPlayer = new CPlayer();
	AddGameObject(pPlayer);

	m_pImage = RESOURCE->LoadImg(L"Field_Back", L"Image\\Field_Back.png");
	LoadBackground(m_pImage);

	m_pImage = RESOURCE->LoadImg(L"Field_Middle", L"Image\\Field_Middle.png");
	LoadMiddleground(m_pImage);

	m_pImage = RESOURCE->LoadImg(L"Cloud", L"Image\\Cloud.png");
	LoadCloud(m_pImage);

	m_pImage = RESOURCE->LoadImg(L"BossMap", L"Image\\BossMap.png");
	CImageObject* pBossMap = new CImageObject;
	pBossMap->SetImage(m_pImage);
	AddGameObject(pBossMap);

	//CWarp* pVillageDoor = new CWarp;
	//pVillageDoor->SetPos(0, 0);
	//pVillageDoor->SetScale(10, 1000);
	//pVillageDoor->SetScene(GroupScene::Stage01);
	//pVillageDoor->SetPlayerStartPos(Vector(1773, 488));
	//pVillageDoor->SetPlayerStartDir(Vector(-1, 0));
	//AddGameObject(pVillageDoor);

	CWarp* pForestDoor = new CWarp;
	pForestDoor->SetPos(0, 500);
	pForestDoor->SetScale(10, 1000);
	pForestDoor->SetScene(GroupScene::Forest);
	pForestDoor->SetPlayerStartPos(Vector(660, 308));
	pForestDoor->SetPlayerStartDir(Vector(-1, 0));
	AddGameObject(pForestDoor);








}

void CSceneBossMap::Enter()
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
	LoadTile(GETPATH + L"Tile\\BossMap.tile");
}

void CSceneBossMap::Update()
{
	if (BUTTONDOWN(VK_ESCAPE))
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Title, 0.25f);
	}

	if (BUTTONDOWN('I'))
	{
		GAME->SetCurScene(GroupScene::BossMap);
		GAME->SetPlayerStartPos(pPlayer->GetPos());
		CHANGESCENE(GroupScene::Inventory);
	}

}

void CSceneBossMap::Render()
{
}

void CSceneBossMap::Exit()
{
}

void CSceneBossMap::Release()
{
}
