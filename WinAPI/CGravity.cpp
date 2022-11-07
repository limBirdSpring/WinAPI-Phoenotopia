#include "framework.h"
#include "CGravity.h"
#include "CTimeManager.h"
#include "CGameObject.h"

CGravity::CGravity()
{
	m_fVelocity = 1;
	m_ground = 0;
	m_platform = 0;
}

CGravity::~CGravity()
{
}

void CGravity::Init()
{
}

void CGravity::Update()
{

}

void CGravity::PhysicsUpdate()
{
	if (m_ground == 0 && m_platform == 0)
	{
		GetOwner()->SetPos(GetOwner()->GetPos().x, GetOwner()->GetPos().y + DT * m_fVelocity);
		m_fVelocity += 450 * DT;

		if (m_fVelocity > 500)
			m_fVelocity = 500;
	}

}

void CGravity::Render()
{
}

void CGravity::Release()
{
}
