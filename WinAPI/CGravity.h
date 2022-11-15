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
	float m_fVelocity;//�ӵ�
	int m_ground; //������ ����
	int m_platform; //�÷������� ����
	int m_wall; //������ ����

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