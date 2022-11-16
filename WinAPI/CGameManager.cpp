#include "framework.h"
#include "CGameManager.h"
#include "CResourceManager.h"

#include "CCameraManager.h"
#include "CImage.h"

CGameManager::CGameManager()
{

	srand(time(NULL));

	m_bTalk = false;
	hp = 25;
	mp = 300;
	gold = 100;
	m_pUIImage = RESOURCE->LoadImg(L"UI_HpGold", L"Image\\UI_HpGold.png");
	m_pUIHeart = RESOURCE->LoadImg(L"UI_Heart", L"Image\\UI_Heart.png");
	m_pUIMp = RESOURCE->LoadImg(L"UI_Mp", L"Image\\UI_Mp.png");
	m_fHeartScale = 50;
	m_pUIItemGet = RESOURCE->LoadImg(L"UI_ItemGet", L"Image\\UI_ItemGet.png");;
	coolTime = 0;
	m_fUIItemGetX = -187;
	getItemName = L"";

	 UIRender = false;

	 m_vecPlayerPos = {0,0};
}
CGameManager::~CGameManager()
{
	
}


void CGameManager::PushBackInvenItem(const Item item)
{
	if (coolTime <= 0)
		coolTime = 3;
		getItemName = item.name;


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
	if (coolTime <= 0)
		coolTime = 3;
	getItemName = name;

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

bool CGameManager::IsItemInvenItem(const wstring name)
{
	for (int i = 0; i < m_vInventoryItem.size(); i++)
	{
		if (m_vInventoryItem[i].name == name)
		{
			return true;
		}
	}
	return false;
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

bool CGameManager::isItemSetting(const wstring name)
{
	for (int i = 0; i < m_vSetItem.size(); i++)
	{
		if (m_vSetItem[i].name == name)
		{
			return true;
		}
	}
	return false;
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
	frog.text = L"개구리를 잡아서 얻은 개구리 뒷다리. Hp를 6 회복시켜준다.";
	frog.hp = 6;
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

	//아이템
	Item honey;
	honey.name = L"벌꿀";
	honey.img = RESOURCE->LoadImg(L"Item_Honey", L"Image\\Item_Honey.png");
	honey.price = 80;
	honey.type = ItemType::Food;
	honey.text = L"꿀벌이 나르고 다녔던 자연산 꿀이다. Hp를 10 회복시켜준다.";
	honey.hp = 10;
	m_vItem.push_back(honey);

	//퀘스트
	Item zem;
	zem.name = L"젬";
	zem.img = RESOURCE->LoadImg(L"Item_Zem", L"Image\\Item_Zem.png");
	zem.type = ItemType::Quest;
	zem.text = L"반짝거리는 젬이다. 문을 여는 데에 쓸 수 있을 것 같다.";
	m_vItem.push_back(zem);

	//퀘스트
	Item Ghostzem;
	Ghostzem.name = L"고스트의 젬스톤";
	Ghostzem.img = RESOURCE->LoadImg(L"Item_Ghost_Zem", L"Image\\Ghost_Zem.png");
	Ghostzem.type = ItemType::Quest;
	Ghostzem.text = L"반짝거리는 젬이다. 문을 여는 데에 쓸 수 있을 것 같다.";
	m_vItem.push_back(Ghostzem);

	//퀘스트
	Item ring;
	ring.name = L"엄청 비싸보이는 반지";
	ring.img = RESOURCE->LoadImg(L"Item_Rich_Ring", L"Image\\Rich_Ring.png");
	ring.type = ItemType::Quest;
	ring.text = L"팔면 돈을 많이 벌 수 있을 거 같은 희귀한 반지다.";
	m_vItem.push_back(ring);
}

void CGameManager::Update()
{
	hp = clamp(hp, 0, 25);
	m_fHeartScale = hp * 2;

	if (mp != 300) mp += 0.1;

	mp = clamp(mp, 0.f, 300.f);

	if (coolTime <= 0)
		m_fUIItemGetX = -187;
	
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
		RENDER->Image(m_pUIHeart, start.x+43 - m_fHeartScale, start.y+35 - m_fHeartScale, start.x + 43 + m_fHeartScale, start.y+35 + m_fHeartScale);
		RENDER->Image(m_pUIMp, start.x + 145, start.y + 29, start.x + 145 + (mp/2), start.y + 41);
		
		if (isItemSetting(L"방망이"))
		{
			RENDER->Image
			(FindItem(L"방망이").img, 
				start.x +116 - FindItem(L"방망이").img->GetWidth() *0.5, 
				start.y + 35 - FindItem(L"방망이").img->GetHeight() * 0.5, 
				start.x + 116 + FindItem(L"방망이").img->GetWidth() * 0.5, 
				start.y + 35 + FindItem(L"방망이").img->GetHeight() * 0.5);
		}

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

		if (coolTime > 0)
		{
			if (coolTime > 2.6)
				m_fUIItemGetX += DT*450;
			else if (coolTime < 1.4)
				m_fUIItemGetX -= DT*450;

			RENDER->Image(m_pUIItemGet, start.x + m_fUIItemGetX, start.y + 173, start.x + m_fUIItemGetX + m_pUIItemGet->GetWidth() + 40, start.y + 173 + m_pUIItemGet->GetHeight());
			RENDER->Text(getItemName + L" 획득", start.x + 20+m_fUIItemGetX, start.y + 173, start.x + m_fUIItemGetX + 300, start.y + 213);
			coolTime -= DT;
		}
		

		CAMERA->SetScale(scale);
	}
}
void CGameManager::Release()
{

}