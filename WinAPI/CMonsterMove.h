#pragma once
#include "CMonsterState.h"
class CMonsterMove :
	public CMonsterState
{
public:
	CMonsterMove(CMonster* monster) { pMonster = monster; }
	virtual ~CMonsterMove();

	void SetCoolTime(float time) { coolTime = time; }

	void Init() override;
	void Update() override;
	void Release() override;

};

