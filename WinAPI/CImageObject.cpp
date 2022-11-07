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
//	Vector startCameraPos = Vector(CAMERA->GetLookAt().x - (WINSIZEX*0.5), CAMERA->GetLookAt().y - (WINSIZEY * 0.5));
//	Vector endCameraPos = Vector(CAMERA->GetLookAt().x + (WINSIZEX * 0.5), CAMERA->GetLookAt().y + (WINSIZEY * 0.5));
//	
//	Vector startImagePos = Vector(m_vecPos.x, m_vecPos.y);
//	Vector endImagePos = Vector(m_vecPos.x + (float)m_pImage->GetWidth(), m_vecPos.y + (float)m_pImage->GetHeight());
//	
//	if (endImagePos.x < endCameraPos.x)
//	{
//		CImageObject* pOtherImage = this;
//		pOtherImage->SetPos(endImagePos.x, startImagePos.y);
//		pOtherImage->SetDir(Vector(m_vecMoveDir.x, m_vecMoveDir.y));
//		AddGameObject(pOtherImage);
//	}
//	else if (startCameraPos.x < startImagePos.x)
//	{
//		CImageObject* pOtherImage = this;
//		pOtherImage->SetPos(startImagePos.x - m_pImage->GetWidth(), startImagePos.y);
//		pOtherImage->SetDir(Vector(m_vecMoveDir.x, m_vecMoveDir.y));
//		AddGameObject(pOtherImage);
//	}
//	
//	if (endImagePos.x < startCameraPos.x || startImagePos.x > endCameraPos.x)
//	{
//		DELETEOBJECT(this);
//	}


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
