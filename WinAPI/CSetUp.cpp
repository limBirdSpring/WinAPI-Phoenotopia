#include "framework.h"
#include "CSetUp.h"
#include "CImageObject.h"
#include "CImage.h"

CSetUp::CSetUp()
{
	m_pImage = nullptr;
	selectNum = 0;
}

CSetUp::~CSetUp()
{
}

void CSetUp::Init()
{
	m_pImage = RESOURCE->LoadImg(L"SetUp", L"Image\\SetUp.png");
	CImageObject* pImage = new CImageObject;
	pImage->SetImage(m_pImage);
	pImage->SetPos(Vector(0, 0));
	AddGameObject(pImage);

}

void CSetUp::Enter()
{
	selectNum = 0;
	CAMERA->ZoomInOut(1);
	CAMERA->SetMapSize(Vector(m_pImage->GetWidth(), m_pImage->GetHeight()));

	GAME->SetUIRender(false);

	pSe = RESOURCE->FindSound(L"Choice");
	SOUND->Play(pSe);
}

void CSetUp::Update()
{
	if (BUTTONDOWN(VK_UP))
	{
		pSe = RESOURCE->FindSound(L"Cursor");
		SOUND->Play(pSe);
		selectNum--;
	}
	else if (BUTTONDOWN(VK_DOWN))
	{
		pSe = RESOURCE->FindSound(L"Cursor");
		SOUND->Play(pSe);
		selectNum++;
	}

	selectNum = clamp(selectNum, 0, 1);

	if (BUTTONDOWN(VK_ESCAPE))
	{
		GAME->SetUIRender(true);
		pSe = RESOURCE->FindSound(L"Cursor");
		CHANGESCENE(GAME->GetCurScene());
	}

	if (BUTTONDOWN('X'))
	{
		if (selectNum == 0)
		{
			CAMERA->FadeOut(0.25f);
			DELAYCHANGESCENE(GAME->GetCurScene(), 0.25f);
		}
		else
		{
			pSe = RESOURCE->FindSound(L"Choice");
			SOUND->Play(pSe);
			CAMERA->FadeOut(0.25f);
			DELAYCHANGESCENE(GroupScene::Title, 2.f);
		}
	}
}

void CSetUp::Render()
{
	RENDER->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	RENDER->SetBrush(Color(0, 50, 200, 0.5));
	if (selectNum == 0)
		RENDER->SetBrush(Color(0, 50, 200, 0.5));
	else
		RENDER->SetBrush(Color(255, 255, 255, 1));
	RENDER->Text(L"계속하기", 484, 288, 788, 320);

	if (selectNum == 1)
		RENDER->SetBrush(Color(0, 50, 200, 0.5));
	else
		RENDER->SetBrush(Color(255, 255, 255, 1));
	RENDER->Text(L"타이틀 화면으로", 484, 351, 788, 393);

	RENDER->SetBrush(Color(255,255,255,1));
	RENDER->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
}

void CSetUp::Exit()
{
	
	SOUND->Play(pSe);
}

void CSetUp::Release()
{
}
