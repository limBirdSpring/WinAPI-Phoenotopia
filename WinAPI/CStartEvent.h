
#pragma once
#include "CEvent.h"

class CStartEvent :
	public CEvent
{
public:
	CStartEvent(CPlayer* player) { pPlayer = player; };
	virtual ~CStartEvent();

private:

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionStay(CCollider* pOtherCollider) override;

	void Talk();
};