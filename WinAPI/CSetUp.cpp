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
}

void CSetUp::Update()
{
	if (BUTTONDOWN(VK_UP))
	{
		selectNum--;
	}
	else if (BUTTONDOWN(VK_DOWN))
	{
		selectNum++;
	}

	selectNum = clamp(selectNum, 0, 1);

	if (BUTTONDOWN(VK_ESCAPE))
	{
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
			CAMERA->FadeOut(0.25f);
			DELAYCHANGESCENE(GroupScene::Title, 0.25f);
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
	RENDER->Text(L"����ϱ�", 484, 288, 788, 320);

	if (selectNum == 1)
		RENDER->SetBrush(Color(0, 50, 200, 0.5));
	else
		RENDER->SetBrush(Color(255, 255, 255, 1));
	RENDER->Text(L"Ÿ��Ʋ ȭ������", 484, 351, 788, 393);

	RENDER->SetBrush(Color(255,255,255,1));
	RENDER->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
}

void CSetUp::Exit()
{
	GAME->SetUIRender(true);
}

void CSetUp::Release()
{
}
