#pragma once
#include "CNPC.h"

class CTeacher :
	public CNPC
{
public:
	CTeacher();
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