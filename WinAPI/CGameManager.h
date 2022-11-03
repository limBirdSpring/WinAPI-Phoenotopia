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
	CImage* img;	//������ �̹���
	ItemType type;	//������ ����
	int price;		//������ ����
	int num;		//������ ����
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
	bool m_bAttack;
	float m_fAttackTime;


private :
	//�÷��̾� ����
	Vector m_vecPlayerPos;
	Vector m_vecplayerDir;
	int gold;
	int hp;

	unordered_map<string, Item> m_vecInventoryItem; //�κ��丮�� ����ִ� ������
	unordered_map<string, Item> m_vecSetItem; //������ ������

public :

	bool GetAttack() { return m_bAttack; }
	void SetAttack(bool attack) { m_bAttack = attack; }

	float GetAttackTime() { return m_fAttackTime; }
	void SetAttackTime(float time) { m_fAttackTime = time; }


public :
	Vector GetPlayerPos() { return m_vecPlayerPos; }
	void SetPlayerPos(Vector pos) { m_vecPlayerPos = pos; }

	Vector GetPlayerDir() { return m_vecplayerDir; }
	void SetPlayerDir(Vector dir) { m_vecplayerDir = dir; }

	int GetGold() { return gold; }
	void SetGold(int gold) { this->gold = gold; }

	int GetHp() { return hp; }
	void SetHp(int hp) { this->hp = hp; }



private :
	void Init();
	void Update();
	void Release();


};

#define	GAME				CGameManager::GetInstance()
