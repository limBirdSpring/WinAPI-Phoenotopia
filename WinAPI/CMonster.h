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

	int m_damageHp; //플레이어가 맞았을 때 얼마나 데미지를 입는지
	unordered_map<MonsterBehavior, CMonsterState*> m_mapMonsterState;

	Vector m_vecLookDir;
	MonsterBehavior m_behavior;



public:
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


