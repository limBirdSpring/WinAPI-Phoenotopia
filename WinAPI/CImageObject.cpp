#include "framework.h"
#include "CImageObject.h"

#include "CRenderManager.h"
#include "CTimeManager.h"
#include "CCameraManager.h"
#include "CEventManager.h"
#include "CScene.h"
#include "CGameObject.h"
#include "CSceneManager.h"
#include "CGameManager.h"

#include "CImage.h"

CImageObject::CImageObject()
{
	m_pImage = nullptr;
	m_fSpeed = 0.f;
	m_vecMoveDir = Vector(0, 0);

	m_vecPos = Vector(0, 0);
}

CImageObject::~CImageObject()
{
}

CImage* CImageObject::GetIamge()
{
    return m_pImage;
}

void CImageObject::SetImage(CImage* pImage)
{
	m_pImage = pImage;
}

void CImageObject::Init()
{

}

void CImageObject::Update()
{

	if (m_fSpeed != 0)
	{
		m_vecPos.x += m_fSpeed * m_vecMoveDir.x * DT;
		m_vecPos.y += m_fSpeed * m_vecMoveDir.y * DT;
	}
}

void CImageObject::Render()
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

void CImageObject::Release()
{
}
