#pragma once
#include "CNPC.h"

class CPlayer;

class CThief :
	public CNPC
{
public:
	CThief(CPlayer* player);
	virtual ~CThief();

private:
	bool isRun;
	float coolTime;
	CSound* pSe;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionStay(CCollider* pOtherCollider) override;

	void Talk();
};