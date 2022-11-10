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


void CGameManager::PushBackInvenItem(const Item item)
{
	for (int i = 0; i < m_vInventoryItem.size(); i++)
	{
		if (m_vInventoryItem[i].name == item.name)
		{
			m_vInventoryItem[i].num++;
			return;
		}
	}
	m_vInventoryItem.push_back(item);
}

void CGameManager::EraseInvenItem(const Item item)
{
	for (int i=0; i< m_vInventoryItem.size();i++)
	{
		if (m_vInventoryItem[i].name == item.name)
		{
			m_vInventoryItem[i].num--;

			if (m_vInventoryItem[i].num == 0)
			{
				m_vInventoryItem.erase(m_vInventoryItem.begin()+i);
			}
			return;
		}

	}
}

void CGameManager::PushBackInvenItem(const wstring name)
{
	for (int i = 0; i < m_vInventoryItem.size(); i++)
	{
		if (m_vInventoryItem[i].name == name)
		{
			m_vInventoryItem[i].num++;
			return;
		}
	}
	for (int i = 0; i < m_vItem.size(); i++)
	{
		if (m_vItem[i].name == name)
		{
			m_vInventoryItem.push_back(m_vItem[i]);
			return;
		}
	}
	assert(0);
}

void CGameManager::EraseInvenItem(const wstring name)
{
	for (int i = 0; i < m_vInventoryItem.size(); i++)
	{
		if (m_vInventoryItem[i].name == name)
		{
			m_vInventoryItem[i].num--;

			if (m_vInventoryItem[i].num == 0)
			{
				m_vInventoryItem.erase(m_vInventoryItem.begin() + i);
			}
			return;
		}

	}
}

void CGameManager::Init()
{
	//무기
	Item bat;
	bat.name = L"방망이";
	bat.img = RESOURCE->LoadImg(L"Item_Bat", L"Image\\Item_Bat.png");
	bat.type = ItemType::Weapon;
	bat.text = L"나무로 된 방망이다. 무기로 쓸 수 있다.";
	m_vItem.push_back(bat);

	//아이템
	Item egg;
	egg.name = L"페로 알";
	egg.img = RESOURCE->LoadImg(L"Item_Egg", L"Image\\Item_Egg.png");
	egg.price = 30;
	egg.type = ItemType::Food;
	egg.text = L"먹음직스러운 페로알이다. Hp를 3 회복시켜준다.";
	egg.hp = 3;
	m_vItem.push_back(egg);

	//아이템
	Item frog;
	frog.name = L"개구리 뒷다리";
	frog.img = RESOURCE->LoadImg(L"Item_Frog", L"Image\\Item_Frog.png");
	frog.price = 30;
	frog.type = ItemType::Food;
	frog.text = L"개구리를 잡아서 얻은 개구리 뒷다리. Hp를 4 회복시켜준다.";
	frog.hp = 4;
	m_vItem.push_back(frog);
}
void CGameManager::Update()
{

}
void CGameManager::Release()
{

}