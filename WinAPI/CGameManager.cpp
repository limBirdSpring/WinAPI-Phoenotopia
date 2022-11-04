#include "framework.h"
#include "CGameManager.h"


CGameManager::CGameManager()
{
	 m_bTalk = false;
	 m_bAttack = false;
	 m_bDamage = false;
	 m_fAttackTime = 0;
	 m_fDamageTime = 0;
	 hp = 30;
	 gold = 100;

	 m_vecPlayerPos = {0,0};
}
CGameManager::~CGameManager()
{

}


void CGameManager::Init()
{

}
void CGameManager::Update()
{

}
void CGameManager::Release()
{

}