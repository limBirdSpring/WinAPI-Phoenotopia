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
	wstring name;	//아이템 이름
	wstring text;	//아이템 설명
	CImage* img;	//아이템 이미지
	ItemType type;	//아이템 종류
	int price = 0;		//아이템 가격
	int num = 1;		//아이템 갯수
	int hp = 0;		//아이템 효과
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
	bool m_bDamage;

	float m_fAttackTime;
	float m_fDamageTime;

	GroupScene m_curScene;

private :
	//플레이어 정보
	Vector m_vecPlayerPos;
	Vector m_vecplayerDir;
	int gold;
	int hp;

	
	
	Vector m_vecStartPos; //맵으로 워프했을 경우 플레이어의 초기 위치

public :
	vector<Item> m_vItem;//아이템 종류
	vector<Item> m_vInventoryItem; //인벤토리에 들어있는 아이템
	vector<Item> m_vSetItem; //착용한 아이템

	bool GetAttack() { return m_bAttack; }
	void SetAttack(bool attack) { m_bAttack = attack; }

	bool GetDamage() { return m_bDamage; }
	void SetDamage(bool damage) { m_bDamage = damage; }

	bool GetTalk() { return m_bTalk; }
	void SetTalk(bool talk) { m_bTalk = talk; }

	float GetAttackTime() { return m_fAttackTime; }
	void SetAttackTime(float time) { m_fAttackTime = time; }

	float GetDamageTime() { return m_fDamageTime; }
	void SetDamageTime(float time) { m_fDamageTime = time; }

	GroupScene GetCurScene() { return m_curScene; }
	void SetCurScene(GroupScene scene) { m_curScene = scene; }


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

private :
	void Init();
	void Update();
	void Release();


};

#define	GAME				CGameManager::GetInstance()
