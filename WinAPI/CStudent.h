#pragma once
#include "CNPC.h"

class CStudent :
	public CNPC
{
public:
	CStudent(CPlayer* player);
	virtual ~CStudent();

private:

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionStay(CCollider* pOtherCollider) override;

	void Talk();
};