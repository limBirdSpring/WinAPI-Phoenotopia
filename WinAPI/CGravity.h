#pragma once
#include "CComponent.h"

class CGameObject;

class CGravity : public CComponent
{
	friend CGameObject;

public:
	CGravity();
	virtual ~CGravity();

private:
	const float gravity = 25.f;
	float m_fVelocity;//속도
	int m_ground; //땅인지 여부
	int m_platform; //플랫폼인지 여부
	int m_wall; //벽인지 여부

	void Init() override;
	void Update() override;
	void PhysicsUpdate() override;
	void Render() override;
	void Release() override;

protected:

	void SetVelocity(float velocity) { m_fVelocity = velocity; }
};

//y = DT x velocity

//velocity - = 25xDT