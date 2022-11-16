#pragma once

class CBoss;

class CBossState
{

public:
	CBossState();
	virtual ~CBossState();

protected:
	CBoss* pBoss;
	float coolTime;

public:

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Release() = 0;

};

