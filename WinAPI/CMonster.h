#pragma once
#include "CGameObject.h"

class CAnimator;
class CImage;

class CMonster :
    public CGameObject
{
public :
	CMonster();
	virtual ~CMonster();


	int m_damageHp; //플레이어가 맞았을 때 얼마나 데미지를 입는지


	virtual void Init() override =0;
	virtual void Update() override = 0;
	virtual void Render() override = 0;
	virtual void Release() override = 0;

	virtual void OnCollisionEnter(CCollider* pOtherCollider) override = 0;
	virtual void OnCollisionStay(CCollider* pOtherCollider) override = 0;
	virtual void OnCollisionExit(CCollider* pOtherCollider) override = 0;
};


