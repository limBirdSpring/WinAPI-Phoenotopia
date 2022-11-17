#pragma once
#include "CEvent.h"

class CPrinceEvent :
	public CEvent
{
public:
	CPrinceEvent(CPlayer* player) { pPlayer = player; };
	virtual ~CPrinceEvent();

private:

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionStay(CCollider* pOtherCollider) override;

	void Talk();
};