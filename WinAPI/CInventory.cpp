#include "framework.h"
#include "CInventory.h"
#include "CResourceManager.h"
#include "CImageObject.h"
#include "CInputManager.h"
#include "CSceneManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"
#include "CGameManager.h"
#include "CRenderManager.h"
#include "CImage.h"
#include "CSelect.h"

CInventory::CInventory()
{
	m_pImage = nullptr;
	selectItem = 0;
	m_pSelect = nullptr;
}

CInventory::~CInventory()
{
}

void CInventory::Init()
{
	m_pImage = RESOURCE->LoadImg(L"Inventory", L"Image\\Inventory.png");
	CImageObject* pImage = new CImageObject;
	pImage->SetImage(m_pImage);
	pImage->SetPos(Vector(0, 0));
	AddGameObject(pImage);

	m_pSelect = new CSelect;
	m_pSelect->SetPos(160, 190);
	AddGameObject(m_pSelect);
	
}

void CInventory::Enter()
{
	m_pSelect->SetPos(160, 190);
	CAMERA->ZoomInOut(1);
	CAMERA->SetMapSize(Vector(m_pImage->GetWidth(), m_pImage->GetHeight()));

}

void CInventory::Update()
{
	if (BUTTONDOWN(VK_ESCAPE))
	{
		CHANGESCENE(GAME->GetCurScene());
	}

	if (BUTTONDOWN(VK_LEFT))
	{

	}
	else if (BUTTONDOWN(VK_RIGHT))
	{

	}
	else if (BUTTONDOWN(VK_UP))
	{

	}
	else if (BUTTONDOWN(VK_DOWN))
	{

	}
}

void CInventory::Render()
{

	//RENDER->Image(GAME->m_vInventoryItem[1].img, 168, 195, 168 + GAME->m_vInventoryItem[1].img->GetWidth(), 195 + GAME->m_vInventoryItem[1].img->GetHeight());

	for (int i = 0; i< GAME->m_vInventoryItem.size(); i++)
	{
		RENDER->Image(
			GAME->m_vInventoryItem[i].img,
			160 + (90 * (i%4)),
			190 + (90 * (i/4)),
			160 + (90 * (i%4)) + GAME->m_vInventoryItem[i].img->GetWidth(),
			190 + (90 * (i/4)) + GAME->m_vInventoryItem[i].img->GetHeight()
		);
	}
}

void CInventory::Exit()
{
}

void CInventory::Release()
{
}
