#pragma once
#include "CGameObject.h"

class CAnimator;
class CImage;
class CMonsterState;

class CMonster :
    public CGameObject
{
public :
	CMonster();
	virtual ~CMonster();

protected :
	int m_damageHp; //�÷��̾ �¾��� �� �󸶳� �������� �Դ���
	
	unordered_map<MonsterBehavior, CMonsterState*> m_mapMonsterState;

	Vector m_vecLookDir;
	MonsterBehavior m_behavior;
	
	float m_startX;
	float m_endX; //���Ϳ� ó����ǥ�� ��������ǥ�� �����Ͽ� ���Ͱ� ���� ������ ������ ���ϰ� ��


public:

	void SetStartXToEndX(float x, float x2) { m_startX = x; m_endX = x2; }
	float GetStartX() { return m_startX; }
	float GetEndX() { return  m_endX; }

	void SetBehavior(MonsterBehavior behavior) { m_behavior = behavior; }
	MonsterBehavior GetBehavoir() { return m_behavior; }

private :
	virtual void Init() override =0;
	virtual void Update() override = 0;
	virtual void Render() override = 0;
	virtual void Release() override = 0;

	virtual void OnCollisionEnter(CCollider* pOtherCollider) override = 0;
	virtual void OnCollisionStay(CCollider* pOtherCollider) override = 0;
	virtual void OnCollisionExit(CCollider* pOtherCollider) override = 0;


};


