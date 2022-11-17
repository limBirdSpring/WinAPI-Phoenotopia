#pragma once
#include "CGameObject.h"

class CAnimator;
class CImage;
class CMonsterState;
class CBossState;

class CBoss :
	public CGameObject
{
public:
	CBoss();
	virtual ~CBoss();

protected:
	int m_damageHp; //�÷��̾ �¾��� �� �󸶳� �������� �Դ���

	unordered_map<BossBehavior, CBossState*> m_mapBossState;

	Vector m_vecLookDir;
	BossBehavior m_behavior;

	float m_startX;
	float m_endX; //���Ϳ� ó����ǥ�� ��������ǥ�� �����Ͽ� ���Ͱ� ���� ������ ������ ���ϰ� ��


public:

	void SetStartXToEndX(float x, float x2) { m_startX = x; m_endX = x2; }
	float GetStartX() { return m_startX; }
	float GetEndX() { return  m_endX; }

	void SetBehavior(BossBehavior behavior) { m_behavior = behavior; }
	BossBehavior GetBehavoir() { return m_behavior; }

private:
	virtual void Init() override = 0;
	virtual void Update() override = 0;
	virtual void Render() override = 0;
	virtual void Release() override = 0;

	virtual void OnCollisionEnter(CCollider* pOtherCollider) override = 0;
	virtual void OnCollisionStay(CCollider* pOtherCollider) override = 0;
	virtual void OnCollisionExit(CCollider* pOtherCollider) override = 0;


};

