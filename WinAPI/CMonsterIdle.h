#pragma once
#include "CMonsterState.h"
class CMonsterIdle :
	public CMonsterState
{
public:
	CMonsterIdle(CMonster* monster) { pMonster = monster; }
	virtual ~CMonsterIdle();



	void Init() override;
	void Update() override;
	void Release() override;

};

