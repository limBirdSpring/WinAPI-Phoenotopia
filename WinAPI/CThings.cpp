#include "framework.h"
#include "CThings.h"

#include "CRenderManager.h"
#include "CTimeManager.h"
#include "CEventManager.h"
#include "CCollider.h"
#include "CGameManager.h"

CThings::CThings()
{
	m_layer = Layer::Things;
}

CThings::~CThings()
{
}

