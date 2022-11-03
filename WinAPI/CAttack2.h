#pragma once
#pragma once
#include "CGameObject.h"
#include "framework.h"
class CAttack2 : public CGameObject
{
public:
	CAttack2();
	virtual ~CAttack2();

private:
	float m_fTime;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionEnter(CCollider* pOtherCollider) override;

};