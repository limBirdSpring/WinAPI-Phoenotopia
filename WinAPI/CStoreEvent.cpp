#include "framework.h"
#include "CStoreEvent.h"

CStoreEvent::~CStoreEvent()
{
}

void CStoreEvent::Init()
{
}

void CStoreEvent::Update()
{
	coolTime += DT;
}

void CStoreEvent::Render()
{
}

void CStoreEvent::Release()
{
}

void CStoreEvent::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CStoreEvent::Talk()
{
}
