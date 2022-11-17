#pragma once
#include "framework.h"

class CCore;
class CImage;



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
	MainQuest mainQuest;

	bool m_bTalk;

	GroupScene m_curScene;

	bool UIRender;

private :
	//�÷��̾� ����
	Vector m_vecPlayerPos;
	Vector m_vecplayerDir;
	int gold;
	int hp;
	float mp;
	
	Vector m_vecStartPos; //������ �������� ��� �÷��̾��� �ʱ� ��ġ 
	Vector m_vecStartDir; //������ �������� ��� �÷��̾��� �ʱ� ����

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

	float GetMp() { return mp; }
	void SetMp(float mp) { this->mp += mp; }

	Vector GetPlayerStartPos() { return m_vecStartPos; }
	void SetPlayerStartPos(Vector pos) { m_vecStartPos = pos; }

	Vector GetPlayerStartDir() { return m_vecStartDir; }
	void SetPlayerStartDir(Vector Dir) { m_vecStartDir = Dir; }


	//TODO : �������� PushBack���� �� '������ ȹ��' UI �߱� 
public :
	void PushBackInvenItem(const Item item);
	void EraseInvenItem(const Item item);
	void PushBackInvenItem(const wstring name);
	void EraseInvenItem(const wstring name);
	bool IsItemInvenItem(const wstring name);
	Item FindItem(const wstring name);
	bool isItemSetting(const wstring name);

	void ResetGame();

//UI�̹���
private :
	CImage* m_pUIImage; //UI�̹���
	CImage* m_pUIHeart; //��Ʈ �̹���
	CImage* m_pUIMp; //Mp�̹���
	CImage* m_pUIItemGet;
	float coolTime;
	float m_fUIItemGetX;
	wstring getItemName;
	float m_fHeartScale;

private :
	void Init();
	void Render();
	void Update();
	void Release();


};

#define	GAME				CGameManager::GetInstance()
