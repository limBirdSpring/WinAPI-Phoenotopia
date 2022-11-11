#include "framework.h"
#include "CStateDownJump.h"
#include "CPlayer.h"

CStateDownJump::~CStateDownJump()
{
}

void CStateDownJump::Init()
{
}

void CStateDownJump::Update()
{
	pPlayer->SetGround(0);
	pPlayer->SetPlatform(0);
	pPlayer->SetGravity(1);

	pPlayer->m_behavior = Behavior::Fall;

}

void CStateDownJump::Render()
{
}

void CStateDownJump::Release()
{
}
