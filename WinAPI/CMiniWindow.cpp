#include "framework.h"
#include "CMiniWindow.h"
#include "CResourceManager.h"
#include "CRenderManager.h"
#include "CImage.h"
#include "CGameManager.h"
#include "CInputManager.h"
#include "CEventManager.h"

CMiniWindow::CMiniWindow()
{
	m_layer = Layer::Things;
	m_pImage = nullptr;
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(100, 100);
	select = 0;
	selectItem = 0;
}

CMiniWindow::~CMiniWindow()
{

}

void CMiniWindow::Init()
{
	m_pImage = RESOURCE->LoadImg(L"UI_MiniWindow", L"Image\\UI_MiniWindow.png");
}

void CMiniWindow::Update()
{
	if (BUTTONDOWN(VK_UP))
	{
		select--;
		pSe = RESOURCE->FindSound(L"Cursor");
		SOUND->Play(pSe);
	}
	else if (BUTTONDOWN(VK_DOWN))
	{
		select++;
		pSe = RESOURCE->FindSound(L"Cursor");
		SOUND->Play(pSe);
	}
	
	select = clamp(select, 0, 1);

	if (BUTTONDOWN('X'))
	{
		pSe = RESOURCE->FindSound(L"Cursor");
		SOUND->Play(pSe);
		DELETEOBJECT(this);
	}
}

void CMiniWindow::Render()
{
	if (selectItem < GAME->m_vInventoryItem.size())
	{
		RENDER->Image(m_pImage, m_vecPos.x + 50, m_vecPos.y + 50, m_vecPos.x + 50 + 100, m_vecPos.y + 50 + 100);

		RENDER->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

		if (GAME->m_vInventoryItem[selectItem].type == ItemType::Weapon)
		{
			RENDER->Text(L"ÀåÂø\n´Ý±â", m_vecPos.x + 50, m_vecPos.y + 50, m_vecPos.x + 50 + 100, m_vecPos.y + 50 + 100);

			RENDER->SetBrush(Color(0, 50, 200, 0.5));
			if (select == 0)
			{
				RENDER->Text(L"ÀåÂø\n", m_vecPos.x + 50, m_vecPos.y + 50, m_vecPos.x + 50 + 100, m_vecPos.y + 50 + 100);
			}
			else
			{
				RENDER->Text(L"\n´Ý±â", m_vecPos.x + 50, m_vecPos.y + 50, m_vecPos.x + 50 + 100, m_vecPos.y + 50 + 100);
			}
			RENDER->SetBrush(Color(255, 255, 255, 255));
		}
		else if (GAME->m_vInventoryItem[selectItem].type == ItemType::Food)
		{
			RENDER->Text(L"¸Ô±â\n´Ý±â", m_vecPos.x + 50, m_vecPos.y + 50, m_vecPos.x + 50 + 100, m_vecPos.y + 50 + 100);

			RENDER->SetBrush(Color(0, 50, 200, 0.5));
			if (select == 0)
			{
				RENDER->Text(L"¸Ô±â\n", m_vecPos.x + 50, m_vecPos.y + 50, m_vecPos.x + 50 + 100, m_vecPos.y + 50 + 100);
			}
			else
			{
				RENDER->Text(L"\n´Ý±â", m_vecPos.x + 50, m_vecPos.y + 50, m_vecPos.x + 50 + 100, m_vecPos.y + 50 + 100);
			}
			RENDER->SetBrush(Color(255, 255, 255, 255));
		}
		RENDER->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	}
}

void CMiniWindow::Release()
{
}
