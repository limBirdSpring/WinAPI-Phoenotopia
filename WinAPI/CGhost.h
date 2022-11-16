#pragma once
#include "CBoss.h"

class CAnimator;
class CImage;

class CGhost :
	public CBoss
{
public:
	CGhost();
	virtual ~CGhost();

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

