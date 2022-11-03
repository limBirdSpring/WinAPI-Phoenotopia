#pragma once
#include "CGameObject.h"
#include "framework.h"
class CCritical: public CGameObject
{
public:
	CCritical();
	virtual ~CCritical();

private:
	float m_fTime;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionEnter(CCollider* pOtherCollider) override;

};