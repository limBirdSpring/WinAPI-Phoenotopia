#pragma once
#include "CThings.h"

#include "framework.h"

class CTalkBox;

class CStatue :
	public CThings
{
public:
	CStatue();
	virtual ~CStatue();

public:
	bool isStatueOn;
	wstring dir;
	CTalkBox* pTalkBox;

	wstring m_strDialogue;
	int talk; //대화순서

private:
	CSound* pSe;

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;

	void Talk();
};