
#pragma once
#include "CNPC.h"

class CLisa :
	public CNPC
{
public:
	CLisa();
	virtual ~CLisa();

private:

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionStay(CCollider* pOtherCollider) override;

	void Talk();
};