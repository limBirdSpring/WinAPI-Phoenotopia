#include "framework.h"
#include "CStateBat.h"

CStateBat::~CStateBat()
{
}

void CStateBat::Init()
{
}

void CStateBat::Update()
{
	if (coolTime == 0)
	{
		pSe = RESOURCE->FindSound(L"AttackSlow");
		SOUND->Play(pSe);
	}
	coolTime += DT;
}

void CStateBat::Render()
{
}

void CStateBat::Release()
{
}
