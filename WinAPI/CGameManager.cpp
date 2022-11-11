#include "framework.h"
#include "CGameManager.h"
#include "CResourceManager.h"

#include "CCameraManager.h"
#include "CImage.h"

CGameManager::CGameManager()
{
	 m_bTalk = false;
	 m_bAttack = false;
	 m_bDamage = false;
	 m_fAttackTime = 0;
	 m_fDamageTime = 0;
	 hp = 30;
	 gold = 100;
	 m_pUIImage = RESOURCE->LoadImg(L"UI_HpGold", L"Image\\UI_HpGold.png");
	 
	 UIRender = false;

	 m_vecPlayerPos = {0,0};
}
CGameManager::~CGameManager()
{
	
}


void CGameManager::PushBackInvenItem(const Item item)
{
	if (m_vInventoryItem.size() > 12)
		return;
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
	if (m_vInventoryItem.size() > 12)
		return;
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

Item CGameManager::FindItem(const wstring name)
{
	for (int i = 0; i < m_vItem.size(); i++)
	{
		if (m_vItem[i].name == name)
		{
			return m_vItem[i];
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
	frog.price = 0;
	frog.type = ItemType::Food;
	frog.text = L"개구리를 잡아서 얻은 개구리 뒷다리. Hp를 4 회복시켜준다.";
	frog.hp = 4;
	m_vItem.push_back(frog);

	//아이템
	Item milk;
	milk.name = L"우유";
	milk.img = RESOURCE->LoadImg(L"Item_Milk", L"Image\\Item_Milk.png");
	milk.price = 45;
	milk.type = ItemType::Food;
	milk.text = L"목장에서 갓 짜낸 신선한 우유. Hp를 5 회복시켜준다.";
	milk.hp = 5;
	m_vItem.push_back(milk);

	//아이템
	Item mill;
	mill.name = L"도시락";
	mill.img = RESOURCE->LoadImg(L"Item_Mill", L"Image\\Item_Mill.png");
	mill.price = 100;
	mill.type = ItemType::Food;
	mill.text = L"고기반찬이 들어있는 맛있는 특제 도시락. Hp를 20 회복시켜준다.";
	mill.hp = 20;
	m_vItem.push_back(mill);

	//퀘스트
	Item zem;
	zem.name = L"젬";
	zem.img = RESOURCE->LoadImg(L"Item_Zem", L"Image\\Item_Zem.png");
	zem.type = ItemType::Quest;
	zem.text = L"반짝거리는 젬이다. 문을 여는 데에 쓸 수 있을 것 같다.";
	m_vItem.push_back(zem);
}

void CGameManager::Update()
{
	hp = clamp(hp, 0, 30);
}
void CGameManager::Render()
{
	if (UIRender == true)
	{
		// UI 출력
		float scale = CAMERA->GetScale();
		CAMERA->SetScale(1);
		
		
		Vector start = CAMERA->ScreenToWorldPoint(Vector(0,0));
		RENDER->Image(m_pUIImage, start.x, start.y, start.x + m_pUIImage->GetWidth(), start.y + m_pUIImage->GetHeight());
		RENDER->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		RENDER->SetTextFormat(L"둥근모꼴",
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			30.f,
			L"ko");
		RENDER->Text(to_wstring(hp), start.x + 19, start.y + 18, start.x + 66, start.y + 49);//HP
		RENDER->Text(to_wstring(gold), start.x + 1143, start.y + 24, start.x + 1235, start.y + 49);//Gold
		RENDER->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		RENDER->SetTextFormat(L"둥근모꼴",
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			25.f,
			L"ko");
		CAMERA->SetScale(scale);

		
	}
}
void CGameManager::Release()
{

}