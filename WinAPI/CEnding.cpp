#include "framework.h"
#include "CEnding.h"
#include "CImageObject.h"

CEnding::CEnding()
{
}

CEnding::~CEnding()
{
}

void CEnding::Init()
{
}

void CEnding::Enter()
{
	m_pImage = RESOURCE->LoadImg(L"Dead", L"Image\\Dead.png");
	CImageObject* pDead = new CImageObject;
	pDead->SetImage(m_pImage);
	AddGameObject(pDead);

	CAMERA->ZoomInOut(1);	
	GAME->SetUIRender(false);
}

void CEnding::Update()
{
}

void CEnding::Render()
{
}

void CEnding::Exit()
{
}

void CEnding::Release()
{
}
