#include "framework.h"
#include "CFrontImage.h"

#include "CRenderManager.h"
#include "CTimeManager.h"
#include "CCameraManager.h"
#include "CEventManager.h"
#include "CScene.h"
#include "CGameObject.h"
#include "CSceneManager.h"
#include "CGameManager.h"

#include "CImage.h"

CFrontImage::CFrontImage()
{
	m_pImage = nullptr;
	m_fSpeed = 0.f;
	m_vecMoveDir = Vector(0, 0);
	m_layer = Layer::FrontGround;
	m_vecPos = Vector(0, 0);
}

CFrontImage::~CFrontImage()
{
}

CImage* CFrontImage::GetIamge()
{
	return m_pImage;
}

void CFrontImage::SetImage(CImage* pImage)
{
	m_pImage = pImage;
}

void CFrontImage::Init()
{

}

void CFrontImage::Update()
{

	if (m_fSpeed != 0)
	{
		m_vecPos.x += m_fSpeed * m_vecMoveDir.x * DT;
		m_vecPos.y += m_fSpeed * m_vecMoveDir.y * DT;
	}
}

void CFrontImage::Render()
{
	if (nullptr != m_pImage)
	{

		RENDER->Image(
			m_pImage,
			m_vecPos.x,
			m_vecPos.y,
			m_vecPos.x + (float)m_pImage->GetWidth(),
			m_vecPos.y + (float)m_pImage->GetHeight()
		);
	}
}

void CFrontImage::Release()
{
}
