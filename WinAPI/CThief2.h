#pragma once
#include "CNPC.h"

class CPlayer;

class CThief2 :
	public CNPC
{
public:
	CThief2(CPlayer* player);
	virtual ~CThief2();

private:

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionStay(CCollider* pOtherCollider) override;

	void Talk();
};