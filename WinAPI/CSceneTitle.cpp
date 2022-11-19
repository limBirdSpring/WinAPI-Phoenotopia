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
#include "CGameManager.h"
#include "CImageObject.h"
#include "CFrontImage.h"

CSceneTitle::CSceneTitle()
{
	coolTime = -1;
}

CSceneTitle::~CSceneTitle()
{
}

void CSceneTitle::Init()
{
	
	pLoad_Screen = RESOURCE->LoadImg(L"Title", L"Image\\Title.png");
	pTitleObject = new CImageObject;
	pTitleObject->SetImage(pLoad_Screen);
	pTitleObject->SetPos(0, 0);
	AddGameObject(pTitleObject);

	pLoad_Screen = RESOURCE->LoadImg(L"Title_Front", L"Image\\Title_Front.png");
	pTitle_Front = new CFrontImage;
	pTitle_Front->SetPos(0, 0);
	pTitle_Front->SetImage(pLoad_Screen);
	AddGameObject(pTitle_Front);

	pTitle = RESOURCE->LoadImg(L"Title_Text", L"Image\\Title_Text.png");
}

void CSceneTitle::Enter()
{

	coolTime = -1;
	textAlpha = 0;

	pTitleObject->SetPos(0, 0);
	pTitle_Front->SetPos(0, 0);

	GAME->SetUIRender(false);
	GAME->SetBossHpBarRender(false);
	CAMERA->FadeIn(0.25f);
	CAMERA->ZoomInOut(1);

	pLoad_BGM = RESOURCE->FindSound(L"Title");
	SOUND->Play(pLoad_BGM, 1.f, true);
	
	
	CAMERA->SetMapSize(Vector(0, 0));
}

void CSceneTitle::Update()
{
	if (textAlpha <= 0)
		textAlphaDir = 1;
	else if (textAlpha >= 1)
		textAlphaDir = -1;

	textAlpha += DT * textAlphaDir;


	if (coolTime > 0)
	{
		if (pTitleObject->GetPos().y > -(pTitleObject->GetIamge()->GetHeight() - WINSIZEY))
			pTitleObject->SetPos(pTitleObject->GetPos().x, pTitleObject->GetPos().y - DT * 800);
		pTitle_Front->SetPos(pTitle_Front->GetPos().x, pTitle_Front->GetPos().y - DT * 200);
		coolTime -= DT;
	}
	else
	{
		if (pTitleObject->GetPos().y > -(pTitleObject->GetIamge()->GetHeight() - WINSIZEY))
			pTitleObject->SetPos(pTitleObject->GetPos().x, pTitleObject->GetPos().y - DT * 30);
	}


	if (coolTime < 0 && coolTime != -1)
	{
		if (pTitleObject->GetPos().y > -(pTitleObject->GetIamge()->GetHeight() - WINSIZEY))
			pTitleObject->SetPos(pTitleObject->GetPos().x, pTitleObject->GetPos().y - DT * 800);
		pTitle_Front->SetPos(pTitle_Front->GetPos().x, pTitle_Front->GetPos().y - DT * 200);

		SOUND->FadeOut(pLoad_BGM, 1.f, 0);
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::GailRoom, 2.f);
		GAME->SetPlayerStartPos(Vector(400, 398));

	}

	if (BUTTONDOWN(VK_F1))
	{
		CHANGESCENE(GroupScene::TileTool);
	}
	if (BUTTONDOWN('X'))
	{
		coolTime = 1.5;
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
	RENDER->Image(pTitle,0,0,pTitle->GetWidth(), pTitle->GetHeight());

	if (coolTime == -1)
	{
		RENDER->Text(L"press 'X' to start",
			WINSIZEX * 0.5f - 140,
			WINSIZEY * 0.5f + 200,
			WINSIZEX * 0.5f + 150,
			WINSIZEY * 0.5f + 330,
			Color(255, 255, 255, textAlpha),
			30.f);
	}
}

void CSceneTitle::Exit()
{
	
}

void CSceneTitle::Release()
{
}
