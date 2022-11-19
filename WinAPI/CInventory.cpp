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
#include "CMiniWindow.h"
#include "CGameObject.h"

CInventory::CInventory()
{
	m_pImage = nullptr;
	selectItem = 0;
	m_pSelect = nullptr;
	m_pMiniWindow = nullptr;
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
	pSe = RESOURCE->FindSound(L"Choice");
	SOUND->Play(pSe);
}

void CInventory::Update()
{
	

	if (m_pMiniWindow != nullptr) //¾ÆÀÌÅÛ ÀåÂø ¹× ¸Ô±â
	{
		if (m_pMiniWindow->GetReserveDelete()&&m_pMiniWindow->select == 0)
		{
			if (GAME->m_vInventoryItem[selectItem].type == ItemType::Weapon)
			{
				GAME->m_vSetItem.push_back(GAME->m_vInventoryItem[selectItem]);

				pSe = RESOURCE->FindSound(L"Equip");
				SOUND->Play(pSe);

			}
			else if (GAME->m_vInventoryItem[selectItem].type == ItemType::Food)
			{
				GAME->SetHp(GAME->m_vInventoryItem[selectItem].hp);

				pSe = RESOURCE->FindSound(L"Heal2");
				SOUND->Play(pSe);
			}
			GAME->EraseInvenItem(GAME->m_vInventoryItem[selectItem]);

			m_pMiniWindow = nullptr;
		}
		else if (m_pMiniWindow->GetReserveDelete() && m_pMiniWindow->select == 1)
			m_pMiniWindow = nullptr;
		
		return;
	}

	if (BUTTONDOWN(VK_ESCAPE))
	{
		CHANGESCENE(GAME->GetCurScene());
	}

	if (BUTTONDOWN('I'))
	{
		CHANGESCENE(GAME->GetCurScene());
	}

	if (BUTTONDOWN(VK_LEFT))
	{
		selectItem--;
		pSe = RESOURCE->FindSound(L"Cursor");
		SOUND->Play(pSe);
	}
	else if (BUTTONDOWN(VK_RIGHT))
	{
		selectItem++;
		pSe = RESOURCE->FindSound(L"Cursor");
		SOUND->Play(pSe);
	}
	else if (BUTTONDOWN(VK_UP))
	{
		selectItem-=4;
		pSe = RESOURCE->FindSound(L"Cursor");
		SOUND->Play(pSe);
	}
	else if (BUTTONDOWN(VK_DOWN))
	{
		selectItem += 4;
		pSe = RESOURCE->FindSound(L"Cursor");
		SOUND->Play(pSe);
	}

	selectItem = clamp(selectItem, 0, 11);

	m_pSelect->SetPos(160 + (90 * (selectItem % 4)), 190 + (90 * (selectItem / 4)));

	if (BUTTONDOWN('X') && selectItem < GAME->m_vInventoryItem.size() && GAME->m_vInventoryItem[selectItem].type != ItemType::Quest)
	{
		m_pMiniWindow = new CMiniWindow;
		m_pMiniWindow->SetPos(160 + (90 * (selectItem % 4)), 190 + (90 * (selectItem / 4)));
		m_pMiniWindow->selectItem = this->selectItem;
		AddGameObject(m_pMiniWindow);
		pSe = RESOURCE->FindSound(L"Choice");
		SOUND->Play(pSe);
	}
}

void CInventory::Render()
{

	for (int i = 0; i< GAME->m_vInventoryItem.size(); i++)
	{
		RENDER->Image(
			GAME->m_vInventoryItem[i].img,
			160 + (90 * (i%4)),
			190 + (90 * (i/4)),
			160 + (90 * (i%4)) + GAME->m_vInventoryItem[i].img->GetWidth(),
			190 + (90 * (i/4)) + GAME->m_vInventoryItem[i].img->GetHeight()
		);

		if (GAME->m_vInventoryItem[i].num > 1)
		{
			RENDER->Text(to_wstring(GAME->m_vInventoryItem[i].num),
				160 + (90 * (i % 4)) + 60,
				190 + (90 * (i / 4)) + 20,
				160 + (90 * (i % 4)) + 60 + GAME->m_vInventoryItem[i].img->GetWidth(),
				190 + (90 * (i / 4)) + 20 + GAME->m_vInventoryItem[i].img->GetHeight());
		}
	}

	for (int i = 0; i < GAME->m_vSetItem.size(); i++)
	{
		RENDER->Image(
			GAME->m_vSetItem[i].img,
			576 + (90 * (i % 2)),
			190 + (90 * (i / 2)),
			576 + (90 * (i % 2)) + GAME->m_vSetItem[i].img->GetWidth(),
			190 + (90 * (i / 2)) + GAME->m_vSetItem[i].img->GetHeight()
		);
	}

	if (selectItem < GAME->m_vInventoryItem.size())
	{
		RENDER->Text(GAME->m_vInventoryItem[selectItem].name, 157, 521, 605, 559);
		RENDER->Text(GAME->m_vInventoryItem[selectItem].text, 148, 577, 996, 684);
	}
}

void CInventory::Exit()
{
	pSe = RESOURCE->FindSound(L"Cursor");
	SOUND->Play(pSe);
}

void CInventory::Release()
{
}
