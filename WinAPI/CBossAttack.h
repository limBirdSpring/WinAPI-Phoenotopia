#pragma once
#include "CBossState.h"
class CBossAttack :
	public CBossState
{
public:
	CBossAttack(CBoss* boss) { pBoss = boss; }
	virtual ~CBossAttack();



	void Init() override;
	void Update() override;
	void Release() override;

};

