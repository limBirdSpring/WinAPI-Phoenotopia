
#pragma once
#include "CThings.h"
#include "framework.h"


class CBox :
	public CThings
{
public:
	CBox();
	virtual ~CBox();

private:

public:

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;

};