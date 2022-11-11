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
class CStateAttackReady;
class CStateAttack;
class CStateDownJump;
class CStateAttack2;
class CStateCriticalReady;
class CStateCritical;
class CStateDamage;
class CStateFall;
class CNPC;
class CTeacher;
class CStateTalk;

			 
class CPlayer : public CGameObject
{			
	friend CPlayerState;
	friend CStateWalk;
	friend CStateIdle;
	friend CStateRun;
	friend CStateJump;
	friend CStateDown;
	friend CStateAttackReady;
	friend CStateAttack;
	friend CStateDownJump;
	friend CStateAttack2;
	friend CStateCriticalReady;
	friend CStateCritical;
	friend CStateDamage;
	friend CStateFall;
	friend CStateTalk;
	friend CNPC;
	friend CTeacher;

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


	bool isThingCollision;

	unordered_map<Behavior, CPlayerState*> m_mapPlayerState;

	Vector m_vecLookDir;
	Behavior m_behavior;

	Vector m_vecPlayerGoalPos; //플레이어의 목표지점, (0,0)일 경우 변경하지 않음

public:
	void SetBehavior(Behavior behavior) { m_behavior = behavior; }
	Behavior GetBehavoir() { return m_behavior; }


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