#include "framework.h"
#include "CSelect.h"
#include "CResourceManager.h"
#include "CRenderManager.h"
#include "CImage.h"

CSelect::CSelect()
{
	m_layer = Layer::Things;
	m_pImage = nullptr;
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(100, 100);
}

CSelect::~CSelect()
{
	
}

void CSelect::Init()
{
	m_pImage = RESOURCE->LoadImg(L"UI_Select", L"Image\\UI_Select.png");
}

void CSelect::Update()
{
}

void CSelect::Render()
{
	RENDER->Image(m_pImage, m_vecPos.x, m_vecPos.y, m_vecPos.x + 100, m_vecPos.y + 100);
}

void CSelect::Release()
{
}
