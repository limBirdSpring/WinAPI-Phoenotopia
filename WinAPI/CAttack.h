#pragma once
#pragma once
#include "CGameObject.h"
#include "framework.h"

class CSound;

class CAttack : public CGameObject
{
public:
	CAttack();
	virtual ~CAttack();

private:
	float m_fTime;
	CSound* pSe;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionEnter(CCollider* pOtherCollider) override;

};