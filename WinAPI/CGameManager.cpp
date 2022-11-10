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
	frog.price = 30;
	frog.type = ItemType::Food;
	frog.text = L"�������� ��Ƽ� ���� ������ �޴ٸ�. Hp�� 4 ȸ�������ش�.";
	frog.hp = 4;
	m_vItem.push_back(frog);
}

void CGameManager::Update()
{

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
		CAMERA->SetScale(scale);

		
	}
}
void CGameManager::Release()
{

}