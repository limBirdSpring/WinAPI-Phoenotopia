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
#include "CStatue.h"
#include "CPillarDoor.h"
#include "CFrontImage.h"
#include "CBossAppearBlock.h"
#include "CGhost.h"
#include "CThief2.h"

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

	m_pImage = RESOURCE->LoadImg(L"BossMap_Front", L"Image\\BossMap_Front.png");
	CFrontImage* pBossMap_Front = new CFrontImage;
	pBossMap_Front->SetImage(m_pImage);
	AddGameObject(pBossMap_Front);

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

	CWarp* pPrinceDoor = new CWarp;
	pPrinceDoor->SetPos(1021, 500);
	pPrinceDoor->SetScale(10, 1000);
	pPrinceDoor->SetScene(GroupScene::PrinceForest);
	pPrinceDoor->SetPlayerStartPos(Vector(72, 488));
	pPrinceDoor->SetPlayerStartDir(Vector(1, 0));
	AddGameObject(pPrinceDoor);


	CStatue* pStatue = new CStatue;
	pStatue->SetPos(182, 483);
	AddGameObject(pStatue);

	CStatue* pStatue2 = new CStatue;
	pStatue2->SetPos(136, 483);
	AddGameObject(pStatue2);

	CPillarDoor* pPillarDoor = new CPillarDoor;
	pPillarDoor->SetPos(260, 466);
	pPillarDoor->pStatue = pStatue2;
	AddGameObject(pPillarDoor);

	CPillarDoor* pPillarDoor2 = new CPillarDoor;
	pPillarDoor2->SetPos(300, 466);
	pPillarDoor2->pStatue = pStatue;
	AddGameObject(pPillarDoor2);

	CStatue* pStatue3 = new CStatue;
	pStatue3->SetPos(851, 483);
	AddGameObject(pStatue3);

	CPillarDoor* pPillarDoor3 = new CPillarDoor;
	pPillarDoor3->SetPos(891, 466);
	pPillarDoor3->pStatue = pStatue3;
	AddGameObject(pPillarDoor3);

	CGhost* pGhost = new CGhost;
	pGhost->SetPos(700,477);

	CBossAppearBlock* pBlock = new CBossAppearBlock(pPlayer);
	pBlock->pBoss = pGhost;
	pBlock->pDoor = pPillarDoor2;
	pBlock->SetPos(574,488);
	pBlock->SetScale(10, 500);
	AddGameObject(pBlock);

	CThief2* pThief2 = new CThief2(pPlayer);
	pThief2->SetPos(248,489);
	AddGameObject(pThief2);

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

	if (BUTTONDOWN('I'))
	{
		GAME->SetCurScene(GroupScene::BossMap);
		GAME->SetPlayerStartPos(pPlayer->GetPos());
		CHANGESCENE(GroupScene::Inventory);
	}

	if (GAME->GetHp() <= 0)
	{
		pLoad_BGM = RESOURCE->FindSound(L"BossBattle");
		SOUND->Stop(pLoad_BGM);
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Dead, 1.f);
	}

}

void CSceneBossMap::Render()
{
}

void CSceneBossMap::Exit()
{
	GAME->SetBossHpBarRender(false);
}

void CSceneBossMap::Release()
{
}
