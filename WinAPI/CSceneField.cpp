#include "framework.h"
#include "CSceneField.h"

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

CSceneField::CSceneField()
{
	pPlayer = nullptr;
	m_pImage = nullptr;
}

CSceneField::~CSceneField()
{
}

void CSceneField::Init()
{
	pPlayer = new CPlayer();
	AddGameObject(pPlayer);

	m_pImage = RESOURCE->LoadImg(L"Field_Back", L"Image\\Field_Back.png");
	LoadBackground(m_pImage);

	m_pImage = RESOURCE->LoadImg(L"Field_Middle", L"Image\\Field_Middle.png");
	LoadMiddleground(m_pImage);

	m_pImage = RESOURCE->LoadImg(L"Cloud", L"Image\\Cloud.png");
	LoadCloud(m_pImage);

	m_pImage = RESOURCE->LoadImg(L"Field", L"Image\\Field.png");
	CImageObject* pForest = new CImageObject;
	pForest->SetImage(m_pImage);
	AddGameObject(pForest);

	CWarp* pVillageDoor = new CWarp;
	pVillageDoor->SetPos(0, 0);
	pVillageDoor->SetScale(10, 1000);
	pVillageDoor->SetScene(GroupScene::Stage01);
	pVillageDoor->SetPlayerStartPos(Vector(1773, 488));
	pVillageDoor->SetPlayerStartDir(Vector(-1, 0));
	AddGameObject(pVillageDoor);

	CWarp* pForestDoor = new CWarp;
	pForestDoor->SetPos(1100, 0);
	pForestDoor->SetScale(10, 1000);
	pForestDoor->SetScene(GroupScene::Forest);
	pForestDoor->SetPlayerStartPos(Vector(18, 772));
	pForestDoor->SetPlayerStartDir(Vector(1, 0));
	AddGameObject(pForestDoor);

	CItem* pMill = new CItem;
	pMill->SetPos(598, 420);
	pMill->SetItem(L"µµ½Ã¶ô");
	AddGameObject(pMill);

	CItem* pZem = new CItem;
	pZem->SetPos(334, 70);
	pZem->SetItem(L"Áª");
	AddGameObject(pZem);

	CBox* pBox = new CBox;
	pBox->SetPos(300,496);
	AddGameObject(pBox);

	CSlug* pSlug = new CSlug();
	pSlug->SetStartXToEndX(85, 1027);
	pSlug->SetPos(370, 452);
	AddGameObject(pSlug);

	CTurtle* pTurtle = new CTurtle;
	pTurtle->SetStartXToEndX(944, 985);
	pTurtle->SetPos(945, 136);
	AddGameObject(pTurtle);


	CTurtle* pTurtle2 = new CTurtle;
	pTurtle2->SetStartXToEndX(581, 632);
	pTurtle2->SetPos(600,150);
	AddGameObject(pTurtle2);

	m_vFrog.push_back(new CFrog);
	m_vFrog[0]->SetStartXToEndX(85, 1027);
	m_vFrog[0]->SetPos(1017, 200);
	AddGameObject(m_vFrog[0]);

	m_vFrog.push_back(new CFrog);
	 m_vFrog[1]->SetStartXToEndX(85, 1027);
	 m_vFrog[1]->SetPos(800, 452);
	AddGameObject(m_vFrog[1]);

	m_vFrog.push_back(new CFrog);
	m_vFrog[2]->SetStartXToEndX(85, 1027);
	m_vFrog[2]->SetPos(630, 452);
	AddGameObject(m_vFrog[2]);




}

void CSceneField::Enter()
{
	CAMERA->FadeIn(0.25f);

	//pLoad_BGM = RESOURCE->FindSound(L"Panselo");
	//SOUND->Play(pLoad_BGM, 1, true);


	CAMERA->SetMapSize(Vector(m_pImage->GetWidth(), m_pImage->GetHeight()));
	CAMERA->ZoomInOut(2);
	CAMERA->SetTargetObj(pPlayer);

	m_vFrog[0]->SetPos(1017, 332);
	m_vFrog[1]->SetPos(818, 149);
	m_vFrog[2]->SetPos(615, 442);


	pPlayer->SetPos(GAME->GetPlayerStartPos());
	pPlayer->SetDir(GAME->GetPlayerStartDir());
	pPlayer->SetGravity(1);
	pPlayer->SetGround(0);
	pPlayer->SetPlatform(0);

	CAMERA->FadeIn(0.25f);
	LoadTile(GETPATH + L"Tile\\Field.tile");
}

void CSceneField::Update()
{
	if (BUTTONDOWN(VK_ESCAPE))
	{
		GAME->SetCurScene(GroupScene::Field);
		GAME->SetPlayerStartPos(pPlayer->GetPos());
		CHANGESCENE(GroupScene::SetUp);
	}

	if (BUTTONDOWN('I'))
	{
		GAME->SetCurScene(GroupScene::Field);
		GAME->SetPlayerStartPos(pPlayer->GetPos());
		CHANGESCENE(GroupScene::Inventory);
	}

	if (GAME->GetHp() <= 0)
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Dead, 1.f);
	}

}

void CSceneField::Render()
{
}

void CSceneField::Exit()
{
}

void CSceneField::Release()
{
}
