#pragma once
#include "CBossState.h"
class CBossAppear :
	public CBossState
{
public:
	CBossAppear(CBoss* boss) { pBoss = boss; }
	virtual ~CBossAppear();



	void Init() override;
	void Update() override;
	void Release() override;

};

