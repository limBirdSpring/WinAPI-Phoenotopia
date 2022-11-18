#pragma once
#include "CNPC.h"

class CPlayer;

class CSoldier2 :
	public CNPC
{
public:
	CSoldier2(CPlayer* player);
	virtual ~CSoldier2();

private:

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionStay(CCollider* pOtherCollider) override;

	void Talk();
};