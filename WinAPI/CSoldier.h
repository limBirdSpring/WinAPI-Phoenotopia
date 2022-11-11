#pragma once
#include "CNPC.h"

class CPlayer;

class CSoldier :
	public CNPC
{
public:
	CSoldier(CPlayer* player);
	virtual ~CSoldier();

private:

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionStay(CCollider* pOtherCollider) override;

	void Talk();
};