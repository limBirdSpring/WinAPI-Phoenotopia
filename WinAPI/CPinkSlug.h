
#pragma once
#include "CMonster.h"

class CAnimator;
class CImage;

class CPinkSlug :
	public CMonster
{
public:
	CPinkSlug();
	virtual ~CPinkSlug();

private:

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;


};

