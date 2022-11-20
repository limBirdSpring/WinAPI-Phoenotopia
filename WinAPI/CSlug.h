#pragma once
#include "CMonster.h"

class CAnimator;
class CImage;

class CSlug : public CMonster
{
public:
	CSlug();
	virtual ~CSlug();

private:
	CSound* pSe;

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;


};

