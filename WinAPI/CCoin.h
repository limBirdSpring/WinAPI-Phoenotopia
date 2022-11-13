#pragma once
#include "CThings.h"
#include "framework.h"


class CCoin :
	public CThings
{
public:
	CCoin();
	virtual ~CCoin();

private:
	int price;

public:
	void SetPrice(int price) { this->price = price; }

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;

};