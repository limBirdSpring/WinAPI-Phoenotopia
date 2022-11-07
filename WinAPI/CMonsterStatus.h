#pragma once
#include "CComponent.h"

class CMonsterStatus :
    public CComponent
{

public:
	CMonsterStatus();
	virtual ~CMonsterStatus();

private:

	virtual void Init() override =0;
	virtual void Update() override = 0;
	virtual void PhysicsUpdate() override = 0;
	virtual void Render() override = 0;
	virtual void Release() override = 0;

};

