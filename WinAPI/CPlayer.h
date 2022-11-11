#pragma once
#include "CGameObject.h"

class CImage;
class CAnimator;
class CPlayerState;
class CStateWalk;
class CStateIdle;
class CStateRun;
class CStateJump;
class CStateDown;
class CStateAttckReady;
class CStateAttack;
class CStateDownJump;
class CStateAttack2;
class CStateCriticalReady;
class CStateCritical;
class CStateDamage;
class CStateFall;

			 
class CPlayer : public CGameObject
{			
	friend CPlayerState;
	friend CStateWalk;
	friend CStateIdle;
	friend CStateRun;
	friend CStateJump;
	friend CStateDown;
	friend CStateAttckReady;
	friend CStateAttack;
	friend CStateDownJump;
	friend CStateAttack2;
	friend CStateCriticalReady;
	friend CStateCritical;
	friend CStateDamage;
	friend CStateFall;

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


	float m_fJumpTime;
	bool isThingCollision;

	unordered_map<Behavior, CPlayerState*> m_mapPlayerState;


	Vector m_vecLookDir;
	Behavior m_behavior;
	Behavior m_behaviorSave;
public:
	void SetBehavior(Behavior behavior) { m_behavior = behavior; m_behaviorSave = behavior; }
	Behavior GetBehavoir() { return m_behavior; }


private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	
	void BehaviorAction();
	void AnimatorUpdate();
	void CreateMissile();

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;
};