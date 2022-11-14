#pragma once
#include "CThings.h"
#include "framework.h"

class CMarble :
	public CThings
{
public:
	CMarble();
	virtual ~CMarble();

public:
	bool isMarbleOn;
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