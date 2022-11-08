#pragma once
#include "CGameObject.h"
#include "framework.h"


class CThings :
public CGameObject
{
public:
	CThings();
	virtual ~CThings();

private:

private:
	virtual void Init() override =0;
	virtual void Update() override =0;
	virtual void Render() override =0;
	virtual void Release() override =0;

	virtual void OnCollisionEnter(CCollider* pOtherCollider) override =0;
	virtual void OnCollisionStay(CCollider* pOtherCollider) override =0;
	virtual void OnCollisionExit(CCollider* pOtherCollider) override =0;

};