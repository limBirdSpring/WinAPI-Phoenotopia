#include "framework.h"
#include "CNPC.h"

#include "CRenderManager.h"
#include "CTimeManager.h"
#include "CEventManager.h"
#include "CCollider.h"
#include "CGameManager.h"
#include "CResourceManager.h"
#include "CTalkBox.h"

CNPC::CNPC()
{
	m_layer = Layer::NPC;
	m_strDialogue = L"";
	talk = 0;
	
	m_choose =0;//º±≈√¡ˆ
	m_choosing = 1;
	
	pTalkBox = nullptr;

	changeTalkTopic = 0;
}

CNPC::~CNPC()
{
}

