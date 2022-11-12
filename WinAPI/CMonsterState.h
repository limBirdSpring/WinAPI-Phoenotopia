#pragma once

class CMonster;

class CMonsterState
{

public:
	CMonsterState();
	virtual ~CMonsterState();

protected :
	CMonster* pMonster;
	float coolTime;

public :

	virtual void Init() =0;
	virtual void Update() = 0;
	virtual void Release()= 0;

};

