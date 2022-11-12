#pragma once
#include "CMonsterState.h"
class CMonsterJump :
	public CMonsterState
{
public:
	CMonsterJump(CMonster* monster) { pMonster = monster; }
	virtual ~CMonsterJump();



	void Init() override;
	void Update() override;
	void Release() override;

};

