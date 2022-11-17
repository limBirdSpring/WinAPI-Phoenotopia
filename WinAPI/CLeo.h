#pragma once
#include "CNPC.h"

class CLeo :
	public CNPC
{
public:
	CLeo(CPlayer* player);
	virtual ~CLeo();

private:

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionStay(CCollider* pOtherCollider) override;

	void Talk();
};