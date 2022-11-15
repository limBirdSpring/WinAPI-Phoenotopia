#include "framework.h"
#include "CTalkBox.h"
#include "CImage.h"

CTalkBox::CTalkBox()
{
	m_strDialogue = L"";

	m_pTalkBox = RESOURCE->LoadImg(L"TalkBox", L"Image\\TalkBox.png");

	m_pChoose = RESOURCE->LoadImg(L"Choose", L"Image\\Choose.png");

	m_layer = Layer::TalkBox;
}

CTalkBox::~CTalkBox()
{
}

void CTalkBox::Init()
{
}

void CTalkBox::Update()
{
	if (*m_choose != 0)
	{
		if (BUTTONDOWN(VK_UP))
		{
			(* m_choosing)--;
		}
		if (BUTTONDOWN(VK_DOWN))
		{
			(* m_choosing)++;
		}
		if (*m_choosing <= 0)
			*m_choosing = 1;
		else if (*m_choosing > *m_choose)
			*m_choosing = *m_choose;
	}
}

void CTalkBox::Render()
{
	if (m_strDialogue != L"")
	{
		if (m_strDialogue.length() > 20)
		{
			//RENDER->FillRect(m_vecPos.x - 130, m_vecPos.y - 100, m_vecPos.x + 70, m_vecPos.y - 50, Color(100, 100, 100, 255));
			RENDER->Image(m_pTalkBox, m_vecPos.x - 130, m_vecPos.y - 130, m_vecPos.x + 70, m_vecPos.y - 30);
			RENDER->Text(m_strDialogue, m_vecPos.x - 130 + 10, m_vecPos.y - 130, m_vecPos.x + 70 - 10, m_vecPos.y - 30);

			if (*m_choose != 0)
			{
				RENDER->Image(m_pChoose, m_vecPos.x - 120, m_vecPos.y - 86 + (*m_choosing * 8), m_vecPos.x - 120 + m_pChoose->GetWidth(), m_vecPos.y - 86 + (*m_choosing * 8) + m_pChoose->GetHeight());
			}
		}
		else if (m_strDialogue.length() < 7)
		{
			RENDER->Image(m_pTalkBox, m_vecPos.x - 80, m_vecPos.y - 100, m_vecPos.x + 20, m_vecPos.y - 30);
			RENDER->Text(m_strDialogue, m_vecPos.x - 80 + 10, m_vecPos.y - 100, m_vecPos.x + 20 - 10, m_vecPos.y - 30);
		}
		else
		{
			RENDER->Image(m_pTalkBox, m_vecPos.x - 130, m_vecPos.y - 100, m_vecPos.x + 70, m_vecPos.y - 30);
			RENDER->Text(m_strDialogue, m_vecPos.x - 130 + 10, m_vecPos.y - 100, m_vecPos.x + 70 - 10, m_vecPos.y - 30);
		}
	}
}

void CTalkBox::Release()
{
}
