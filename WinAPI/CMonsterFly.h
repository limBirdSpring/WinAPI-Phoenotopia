#pragma once
#include "CMonsterState.h"
class CMonsterFly :
	public CMonsterState
{
public:
	CMonsterFly(CMonster* monster) { pMonster = monster; }
	virtual ~CMonsterFly();

	Vector playerPos;
	Vector plusPos;

	CSound* pSe;

	float coolTimeDT;

	void Init() override;
	void Update() override;
	void Release() override;

};

