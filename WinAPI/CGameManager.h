#pragma once
#include "framework.h"

class CCore;
class CImage;



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
	MainQuest mainQuest;

	bool m_bTalk;

	GroupScene m_curScene;

	bool UIRender;

private :
	//플레이어 정보
	Vector m_vecPlayerPos;
	Vector m_vecplayerDir;
	int gold;
	int hp;
	float mp;
	
	Vector m_vecStartPos; //맵으로 워프했을 경우 플레이어의 초기 위치 
	Vector m_vecStartDir; //맵으로 워프했을 경우 플레이어의 초기 방향

public :
	vector<Item> m_vItem;//아이템 종류
	vector<Item> m_vInventoryItem; //인벤토리에 들어있는 아이템
	vector<Item> m_vSetItem; //착용한 아이템

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


	//TODO : 아이템을 PushBack했을 때 '아이템 획득' UI 뜨기 
public :
	void PushBackInvenItem(const Item item);
	void EraseInvenItem(const Item item);
	void PushBackInvenItem(const wstring name);
	void EraseInvenItem(const wstring name);
	bool IsItemInvenItem(const wstring name);
	Item FindItem(const wstring name);
	bool isItemSetting(const wstring name);

	void ResetGame();

//UI이미지
private :
	CImage* m_pUIImage; //UI이미지
	CImage* m_pUIHeart; //하트 이미지
	CImage* m_pUIMp; //Mp이미지
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
