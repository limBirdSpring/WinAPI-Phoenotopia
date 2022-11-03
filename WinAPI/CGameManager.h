#pragma once
#include "framework.h"

class CCore;

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
	Vector m_vecPlayerPos;
	Vector m_vecplayerDir;


public :

	bool GetAttack() { return m_bAttack; }
	void SetAttack(bool attack) { m_bAttack = attack; }

	float GetAttackTime() { return m_fAttackTime; }
	void SetAttackTime(float time) { m_fAttackTime = time; }

	Vector GetPlayerPos() { return m_vecPlayerPos; }
	void SetPlayerPos(Vector pos) { m_vecPlayerPos = pos; }

	Vector GetPlayerDir() { return m_vecplayerDir; }
	void SetPlayerDir(Vector dir) { m_vecplayerDir = dir; }

private :
	void Init();
	void Update();
	void Release();


};

#define	GAME				CGameManager::GetInstance()
