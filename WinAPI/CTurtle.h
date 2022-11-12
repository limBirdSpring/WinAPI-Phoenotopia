#pragma once
#include "CMonster.h"

class CAnimator;
class CImage;

class CTurtle :
	public CMonster
{
public:
	CTurtle();
	virtual ~CTurtle();

private:

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;

	void AnimatorUpdate();
};

