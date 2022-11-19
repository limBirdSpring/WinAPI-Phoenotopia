#include "framework.h"
#include "CSceneDead.h"

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

CSceneDead::CSceneDead()
{
	pPlayer = nullptr;
	m_pImage = nullptr;
}

CSceneDead::~CSceneDead()
{
}

void CSceneDead::Init()
{
	pPlayer = new CPlayer();
	AddGameObject(pPlayer);


	GAME->SetUIRender(false);
}

void CSceneDead::Enter()
{


	m_pImage = RESOURCE->LoadImg(L"Dead", L"Image\\Dead.png");
	CImageObject* pDead = new CImageObject;
	pDead->SetImage(m_pImage);
	AddGameObject(pDead);

	pPlayer->SetPos(213, 120);
	pPlayer->SetBehavior(Behavior::Dead);

	CAMERA->SetTargetPos(Vector(213, 120));

	GAME->SetUIRender(false);
	CAMERA->FadeIn(0.25f);

	//pLoad_BGM = RESOURCE->FindSound(L"Panselo");
	//SOUND->Play(pLoad_BGM, 1, true);


	CAMERA->ZoomInOut(3);

	CAMERA->FadeIn(0.25f);
	LoadTile(GETPATH + L"Tile\\Dead.tile");
}

void CSceneDead::Update()
{
	if (BUTTONDOWN('X'))
	{
		//GAME->SetHp(13);
		//CAMERA->FadeOut(0.25f);
		//DELAYCHANGESCENE(GroupScene::Title, 2.f);

		SendMessage(hWnd, WM_CLOSE, 0, 0);//윈도우 핸들에 종료메세지를 넣어줌
	}
	
}

void CSceneDead::Render()
{
	//RENDER->FillRect(0, 0, 1000, 500, Color(0, 0, 0, 1));
	RENDER->Text(L"게일이 쓰러졌다!", 130, 50, 326, 77.6, Color(255,255,255,1), 60);
}

void CSceneDead::Exit()
{
	//GAME->ResetGame();
	//SCENE->ResetScene();
}

void CSceneDead::Release()
{
}
