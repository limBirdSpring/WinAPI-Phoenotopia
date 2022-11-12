#pragma once
#include "CMonsterState.h"
class CMonsterFollow :
    public CMonsterState
{
public:
	CMonsterFollow(CMonster* monster) { pMonster = monster; }
	virtual ~CMonsterFollow();



	void Init() override;
	void Update() override;
	void Release() override;

};

