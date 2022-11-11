#pragma once
#include "CNPC.h"

class CCarol :
	public CNPC
{
public:
	CCarol(CPlayer* player);
	virtual ~CCarol();

private:

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionStay(CCollider* pOtherCollider) override;

	void Talk();
};