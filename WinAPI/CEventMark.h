#pragma once
#include "CNPC.h"

class CEventMark :
	public CNPC
{
public:
	CEventMark(CPlayer* player);
	virtual ~CEventMark();

	wstring m_strSetDialogue;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;

	void Talk();
};