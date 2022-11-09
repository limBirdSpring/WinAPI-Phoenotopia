#include "framework.h"
#include "CGameManager.h"
#include "CResourceManager.h"

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
	//무기
	Item bat;
	bat.name = L"방망이";
	bat.img = RESOURCE->LoadImg(L"Item_Bat", L"Image\\Item_Bat.png");
	bat.type = ItemType::Weapon;
	m_vItem.push_back(bat);

	//아이템
	Item egg;
	egg.name = L"페로알";
	egg.img = RESOURCE->LoadImg(L"Item_Egg", L"Image\\Item_Egg.png");
	egg.price = 30;
	egg.type = ItemType::Food;
	m_vItem.push_back(egg);
}
void CGameManager::Update()
{

}
void CGameManager::Release()
{

}