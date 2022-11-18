#pragma once
#include "CNPC.h"

class CGrandma :
	public CNPC
{
public:
	CGrandma(CPlayer* player);
	virtual ~CGrandma();

private:

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionStay(CCollider* pOtherCollider) override;

	void Talk();

};