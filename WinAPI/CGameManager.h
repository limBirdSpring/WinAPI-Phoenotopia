#pragma once
#include "framework.h"

class CCore;
class CImage;


enum ItemType
{
	Food,
	Weapon,
	Quest,

	Size
};

struct Item
{
	wstring name;	//������ �̸�
	wstring text;	//������ ����
	CImage* img;	//������ �̹���
	ItemType type;	//������ ����
	int price = 0;		//������ ����
	int num = 1;		//������ ����
	int hp = 0;		//������ ȿ��
};


class CGameManager : public SingleTon<CGameManager>
{
	friend CCore;
	friend SingleTon<CGameManager>;

public:
	CGameManager();
	virtual ~CGameManager();

private:
	bool m_bTalk;

	GroupScene m_curScene;

	bool UIRender;

private :
	//�÷��̾� ����
	Vector m_vecPlayerPos;
	Vector m_vecplayerDir;
	int gold;
	int hp;
	
	Vector m_vecStartPos; //������ �������� ��� �÷��̾��� �ʱ� ��ġ 

public :
	vector<Item> m_vItem;//������ ����
	vector<Item> m_vInventoryItem; //�κ��丮�� ����ִ� ������
	vector<Item> m_vSetItem; //������ ������

	bool GetTalk() { return m_bTalk; }
	void SetTalk(bool talk) { m_bTalk = talk; }

	GroupScene GetCurScene() { return m_curScene; }
	void SetCurScene(GroupScene scene) { m_curScene = scene; }

	bool GetUIRender() { return UIRender; }
	void SetUIRender(bool render) { UIRender = render; }


public :
	Vector GetPlayerPos() { return m_vecPlayerPos; }
	void SetPlayerPos(Vector pos) { m_vecPlayerPos = pos; }

	Vector GetPlayerDir() { return m_vecplayerDir; }
	void SetPlayerDir(Vector dir) { m_vecplayerDir = dir; }

	int GetGold() { return gold; }
	void SetGold(int gold) { this->gold += gold; }

	int GetHp() { return hp; }
	void SetHp(int hp) { this->hp += hp; }

	Vector GetPlayerStartPos() { return m_vecStartPos; }
	void SetPlayerStartPos(Vector pos) { m_vecStartPos = pos; }

public :
	void PushBackInvenItem(const Item item);
	void EraseInvenItem(const Item item);
	void PushBackInvenItem(const wstring name);
	void EraseInvenItem(const wstring name);
	Item FindItem(const wstring name);
	bool isItemSetting(const wstring name);

private :
	CImage* m_pUIImage; //UI�̹���


private :
	void Init();
	void Render();
	void Update();
	void Release();


};

#define	GAME				CGameManager::GetInstance()
