#include "framework.h"
#include "CNPC.h"

#include "CRenderManager.h"
#include "CTimeManager.h"
#include "CEventManager.h"
#include "CCollider.h"
#include "CGameManager.h"
#include "CResourceManager.h"

CNPC::CNPC()
{
	m_layer = Layer::NPC;
	m_strDialogue = L"";
	talk = 0;
	m_pTalkBox = RESOURCE->LoadImg(L"TalkBox", L"Image\\TalkBox.png");
	m_choose =0;//선택지
	m_choosing = 1;
	m_pChoose = RESOURCE->LoadImg(L"Choose", L"Image\\Choose.png");//선택지
}

CNPC::~CNPC()
{
}

