
#pragma once
#include "CEvent.h"

class CImageBox;

class CStartEvent :
	public CEvent
{
public:
	CStartEvent(CPlayer* player);
	virtual ~CStartEvent();

private:
	CImageBox* pCake;
	bool cake;


private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionStay(CCollider* pOtherCollider) override;

	void Talk();
};