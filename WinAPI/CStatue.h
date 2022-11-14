#pragma once
#include "CNPC.h"

#include "framework.h"

class CStatue :
	public CNPC
{
public:
	CStatue();
	virtual ~CStatue();

public:
	bool isStatueOn;
	wstring dir;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;

};