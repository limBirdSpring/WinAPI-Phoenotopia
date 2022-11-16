#pragma once
#include "CBoss.h"


class CBossSkill :
	public CGameObject
{
public:
	CBossSkill();
	virtual ~CBossSkill();

public :
	//입력 받을 것 : 위치, 크기, 데미지, 쿨타임

	float idleTime;
	float coolTime;
	int damage;

private:
	float time=0;

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;


};

