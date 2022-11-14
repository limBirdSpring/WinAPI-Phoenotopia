#pragma once
#include "CGameObject.h"
#include "framework.h"

class CMarble : public CGameObject
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