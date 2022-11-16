#pragma once
#include "CBossState.h"
class CBossIdle :
	public CBossState
{
public:
	CBossIdle(CBoss* boss) { pBoss = boss; }
	virtual ~CBossIdle();



	void Init() override;
	void Update() override;
	void Release() override;

};

