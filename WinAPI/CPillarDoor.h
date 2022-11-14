#pragma once
#include "CThings.h"
#include "framework.h"

class CMarble;

class CPillarDoor :
	public CThings
{
public:
	CPillarDoor(CMarble* marble);
	virtual ~CPillarDoor();

public:
	CMarble* pMarble;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;

};