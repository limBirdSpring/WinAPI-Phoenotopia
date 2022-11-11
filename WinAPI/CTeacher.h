#pragma once
#include "CNPC.h"

class CPlayer;

class CTeacher :
	public CNPC
{
public:
	CTeacher(CPlayer* player);
	virtual ~CTeacher();

private:

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionStay(CCollider* pOtherCollider) override;

	void Talk();
};