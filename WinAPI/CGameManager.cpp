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
	//����
	Item bat;
	bat.name = L"�����";
	bat.img = RESOURCE->LoadImg(L"Item_Bat", L"Image\\Item_Bat.png");
	bat.type = ItemType::Weapon;
	bat.text = L"������ �� ����̴�. ����� �� �� �ִ�.";
	m_vItem.push_back(bat);

	//������
	Item egg;
	egg.name = L"��� ��";
	egg.img = RESOURCE->LoadImg(L"Item_Egg", L"Image\\Item_Egg.png");
	egg.price = 30;
	egg.type = ItemType::Food;
	egg.text = L"������������ ��ξ��̴�. Hp�� 3 ȸ�������ش�.";
	egg.hp = 3;
	m_vItem.push_back(egg);

	//������
	Item frog;
	frog.name = L"������ �޴ٸ�";
	frog.img = RESOURCE->LoadImg(L"Item_Frog", L"Image\\Item_Frog.png");
	frog.price = 0;
	frog.type = ItemType::Food;
	frog.text = L"�������� ��Ƽ� ���� ������ �޴ٸ�. Hp�� 6 ȸ�������ش�.";
	frog.hp = 6;
	m_vItem.push_back(frog);

	//������
	Item milk;
	milk.name = L"����";
	milk.img = RESOURCE->LoadImg(L"Item_Milk", L"Image\\Item_Milk.png");
	milk.price = 45;
	milk.type = ItemType::Food;
	milk.text = L"���忡�� �� ¥�� �ż��� ����. Hp�� 5 ȸ�������ش�.";
	milk.hp = 5;
	m_vItem.push_back(milk);

	//������
	Item mill;
	mill.name = L"���ö�";
	mill.img = RESOURCE->LoadImg(L"Item_Mill", L"Image\\Item_Mill.png");
	mill.price = 100;
	mill.type = ItemType::Food;
	mill.text = L"�������� ����ִ� ���ִ� Ư�� ���ö�. Hp�� 20 ȸ�������ش�.";
	mill.hp = 20;
	m_vItem.push_back(mill);

	//������
	Item honey;
	honey.name = L"����";
	honey.img = RESOURCE->LoadImg(L"Item_Honey", L"Image\\Item_Honey.png");
	honey.price = 80;
	honey.type = ItemType::Food;
	honey.text = L"�ܹ��� ������ �ٳ�� �ڿ��� ���̴�. Hp�� 10 ȸ�������ش�.";
	honey.hp = 10;
	m_vItem.push_back(honey);

	//����Ʈ
	Item zem;
	zem.name = L"��";
	zem.img = RESOURCE->LoadImg(L"Item_Zem", L"Image\\Item_Zem.png");
	zem.type = ItemType::Quest;
	zem.text = L"��¦�Ÿ��� ���̴�. ���� ���� ���� �� �� ���� �� ����.";
	m_vItem.push_back(zem);

	//����Ʈ
	Item Ghostzem;
	Ghostzem.name = L"��Ʈ�� ������";
	Ghostzem.img = RESOURCE->LoadImg(L"Item_Ghost_Zem", L"Image\\Ghost_Zem.png");
	Ghostzem.type = ItemType::Quest;
	Ghostzem.text = L"��¦�Ÿ��� ���̴�. ���� ���� ���� �� �� ���� �� ����.";
	m_vItem.push_back(Ghostzem);

	//����Ʈ
	Item ring;
	ring.name = L"��û ��κ��̴� ����";
	ring.img = RESOURCE->LoadImg(L"Item_Rich_Ring", L"Image\\Rich_Ring.png");
	ring.type = ItemType::Quest;
	ring.text = L"�ȸ� ���� ���� �� �� ���� �� ���� ����� ������.";
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
		// UI ���
		float scale = CAMERA->GetScale();
		CAMERA->SetScale(1);
		
		
		Vector start = CAMERA->ScreenToWorldPoint(Vector(0,0));
		RENDER->Image(m_pUIImage, start.x, start.y, start.x + m_pUIImage->GetWidth(), start.y + m_pUIImage->GetHeight());
		RENDER->Image(m_pUIHeart, start.x+43 - m_fHeartScale, start.y+35 - m_fHeartScale, start.x + 43 + m_fHeartScale, start.y+35 + m_fHeartScale);
		RENDER->Image(m_pUIMp, start.x + 145, start.y + 29, start.x + 145 + (mp/2), start.y + 41);
		
		if (isItemSetting(L"�����"))
		{
			RENDER->Image
			(FindItem(L"�����").img, 
				start.x +116 - FindItem(L"�����").img->GetWidth() *0.5, 
				start.y + 35 - FindItem(L"�����").img->GetHeight() * 0.5, 
				start.x + 116 + FindItem(L"�����").img->GetWidth() * 0.5, 
				start.y + 35 + FindItem(L"�����").img->GetHeight() * 0.5);
		}

		RENDER->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		RENDER->SetTextFormat(L"�ձٸ��",
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			30.f,
			L"ko");
		RENDER->Text(to_wstring(hp), start.x + 19, start.y + 18, start.x + 66, start.y + 49);//HP
		RENDER->Text(to_wstring(gold), start.x + 1143, start.y + 24, start.x + 1235, start.y + 49);//Gold

		RENDER->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		RENDER->SetTextFormat(L"�ձٸ��",
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
			RENDER->Text(getItemName + L" ȹ��", start.x + 20+m_fUIItemGetX, start.y + 173, start.x + m_fUIItemGetX + 300, start.y + 213);
			coolTime -= DT;
		}
		

		CAMERA->SetScale(scale);
	}
}
void CGameManager::Release()
{

}