#pragma once
#include "CGameObject.h"

class CImage;
class CAnimator;

class CPlayer : public CGameObject
{
public:
	CPlayer();
	virtual ~CPlayer();

private:

	CImage* m_pIdleImage;
	CImage* m_pMoveImage;
	CImage* m_pRunImage;
	CImage* m_pJumpImage;
	CImage* m_pDownImage;
	CImage* m_pAttackImage;
	CImage* m_pAttack2Image;
	CImage* m_pCriticalImage;
	CImage* m_pAttackReadyImage;
	CImage* m_pDamageImage;



	Vector m_vecLookDir;
	Behavior m_behavior;



private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void AnimatorUpdate();
	void CreateMissile();

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;
};