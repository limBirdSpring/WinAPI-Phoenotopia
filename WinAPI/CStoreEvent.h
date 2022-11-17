
#pragma once
#include "CEvent.h"
class CStoreEvent :
	public CEvent
{
public:
	CStoreEvent(CPlayer* player) { pPlayer = player; };
	virtual ~CStoreEvent();

private:

	int quest;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionStay(CCollider* pOtherCollider) override;

	void Talk();
};