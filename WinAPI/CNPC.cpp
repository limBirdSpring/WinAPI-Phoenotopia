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
}

CNPC::~CNPC()
{
}

