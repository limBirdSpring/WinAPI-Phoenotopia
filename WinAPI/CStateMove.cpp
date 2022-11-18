#include "framework.h"
#include "CStateMove.h"
#include "CPlayer.h"

CStateMove::~CStateMove()
{
}

void CStateMove::Init()
{
}

void CStateMove::Update()
{
	pPlayer->SetSpeed(80);
	pPlayer->SetPos(pPlayer->GetPos().x + pPlayer->GetSpeed() * pPlayer->GetDir().x * DT, pPlayer->GetPos().y);
}

void CStateMove::Render()
{
}

void CStateMove::Release()
{
}
