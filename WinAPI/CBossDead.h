#pragma once
#include "CBossState.h"
class CBossDead :
	public CBossState
{
public:
	CBossDead(CBoss* boss) { pBoss = boss; }
	virtual ~CBossDead();



	void Init() override;
	void Update() override;
	void Release() override;

};

