#include "framework.h"
#include "CSceneTitle.h"

#include "WinAPI.h"
#include "CRenderManager.h"
#include "CInputManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"
#include "CImage.h"
#include "CResourceManager.h"

CSceneTitle::CSceneTitle()
{
}

CSceneTitle::~CSceneTitle()
{
}

void CSceneTitle::Init()
{
	pLoad_Screen = RESOURCE->LoadImg(L"Load_Screen", L"Image\\Load_Screen.png");
	
}

void CSceneTitle::Enter()
{
	CAMERA->FadeIn(0.25f);
	CAMERA->ZoomInOut(1);
}

void CSceneTitle::Update()
{
	if (BUTTONDOWN(VK_F1))
	{
		CHANGESCENE(GroupScene::TileTool);
	}
	if (BUTTONDOWN(VK_SPACE))
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Stage01, 0.25f);
	}
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
