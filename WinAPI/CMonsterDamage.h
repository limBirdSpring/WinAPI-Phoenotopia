#pragma once
#include "CMonsterState.h"
class CMonsterDamage :
	public CMonsterState
{
public:
	CMonsterDamage(CMonster* monster) { pMonster = monster; }
	virtual ~CMonsterDamage();



	void Init() override;
	void Update() override;
	void Release() override;

};

