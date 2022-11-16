#pragma once
#include "CBossState.h"
class CBossAttack2 :
	public CBossState
{
public:
	CBossAttack2(CBoss* boss) { pBoss = boss; }
	virtual ~CBossAttack2();



	void Init() override;
	void Update() override;
	void Release() override;

};

