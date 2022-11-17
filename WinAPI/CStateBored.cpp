#include "framework.h"
#include "CStateBored.h"
#include "CPlayer.h"

CStateBored::CStateBored(CPlayer* player)
{
}

CStateBored::~CStateBored()
{
}

void CStateBored::Init()
{
}

void CStateBored::Update()
{
	coolTime += DT;

	if (coolTime > 2)
	{
		coolTime = 0;
		pPlayer->SetBehavior(Behavior::Talk);
	}
}

void CStateBored::Render()
{
}

void CStateBored::Release()
{
}
