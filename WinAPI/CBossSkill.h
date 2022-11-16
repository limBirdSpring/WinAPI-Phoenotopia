#pragma once
#include "CBoss.h"


class CBossSkill :
	public CGameObject
{
public:
	CBossSkill();
	virtual ~CBossSkill();

public :
	//�Է� ���� �� : ��ġ, ũ��, ������, ��Ÿ��

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

