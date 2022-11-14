#include "framework.h"
#include "CPillarDoor.h"
#include "CMarble.h"

CPillarDoor::CPillarDoor(CMarble* marble)
{
	pMarble = marble;
}

CPillarDoor::~CPillarDoor()
{
}

void CPillarDoor::Init()
{
}

void CPillarDoor::Update()
{
	if (pMarble->isMarbleOn)
	{

	}
	else
	{

	}
}

void CPillarDoor::Render()
{
}

void CPillarDoor::Release()
{
}

void CPillarDoor::OnCollisionEnter(CCollider* pOtherCollider)
{
}

void CPillarDoor::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CPillarDoor::OnCollisionExit(CCollider* pOtherCollider)
{
}
