#include "framework.h"
#include "CSceneTitle.h"

#include "WinAPI.h"
#include "CRenderManager.h"
#include "CInputManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"
#include "CImage.h"
#include "CResourceManager.h"
#include "CSoundManager.h"

CSceneTitle::CSceneTitle()
{
}

CSceneTitle::~CSceneTitle()
{
}

void CSceneTitle::Init()
{
	
	
}

void CSceneTitle::Enter()
{
	CAMERA->FadeIn(0.25f);
	CAMERA->ZoomInOut(1);

	//pLoad_BGM = RESOURCE->FindSound(L"Title");
	//SOUND->Play(pLoad_BGM, 1.f, true);
	
	pLoad_Screen = RESOURCE->LoadImg(L"Load_Screen", L"Image\\Load_Screen.png");
	CAMERA->SetMapSize(Vector(0, 0));
}

void CSceneTitle::Update()
{
	if (BUTTONDOWN(VK_F1))
	{
		CHANGESCENE(GroupScene::TileTool);
	}
	if (BUTTONDOWN(VK_SPACE))
	{
		//SOUND->FadeOut(pLoad_BGM, 3.f, 0);
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Stage01, 0.25f);
	}
	if (BUTTONDOWN(VK_F2))
	{
		//SOUND->FadeOut(pLoad_BGM, 3.f, 0);
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::GailRoom, 0.25f);
	}
	//if (BUTTONDOWN(VK_F2))
	//{
	//	SOUND->FadeOut(pLoad_BGM, 2, 0);
	//}
	//if (BUTTONDOWN(VK_F3))
	//{
	//	SOUND->FadeIn(pLoad_BGM, 2, 1, true);
	//}
}

void CSceneTitle::Render()
{

	RENDER->Text(L"press space to start",
		WINSIZEX * 0.5f - 100,
		WINSIZEY * 0.5f - 10,
		WINSIZEX * 0.5f + 100,
		WINSIZEY * 0.5f + 10,
		Color(0, 0, 0, 1.f),
		20.f);
	RENDER->Image(pLoad_Screen,0,0,WINSIZEX,WINSIZEY);
}

void CSceneTitle::Exit()
{
	
}

void CSceneTitle::Release()
{
}
