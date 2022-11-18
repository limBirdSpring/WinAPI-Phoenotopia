#pragma once
#include "CNPC.h"

class CBoy :
	public CNPC
{
public:
	CBoy(CPlayer* player);
	virtual ~CBoy();

private:

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionStay(CCollider* pOtherCollider) override;

	void Talk();

};