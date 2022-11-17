#include "framework.h"
#include "CEvent.h"

CEvent::CEvent()
{
	m_layer = Layer::NPC;
	m_strDialogue = L"";
	talk = 0;

	m_choose = 0;//º±≈√¡ˆ
	m_choosing = 1;

	pTalkBox = nullptr;

	changeTalkTopic = 0;
}

CEvent::~CEvent()
{
}
