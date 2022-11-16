#pragma once
#include "CBossState.h"
class CBossMove :
	public CBossState
{
public:
	CBossMove(CBoss* boss) { pBoss = boss; }
	virtual ~CBossMove();



	void Init() override;
	void Update() override;
	void Release() override;

};

