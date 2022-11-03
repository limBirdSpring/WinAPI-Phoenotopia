#include "framework.h"
#include "CLineMove.h"
#include "CTimeManager.h"
#include "CGameObject.h"

CLineMove::CLineMove()
{
	m_vecStart = {0,0};
	m_vecEnd = {0,0};

	m_fSpeed = 0;

	repeat = false;
}

CLineMove::~CLineMove()
{
}

void CLineMove::Init()
{
}

void CLineMove::Update()
{
	Vector pos = this->GetOwner()->GetPos();

	if (repeat == false)
	{
		if (pos.x < m_vecEnd.x)
			pos.x += m_fSpeed * DT;
		else
			repeat = true;
	}
	else
	{
		if (pos.x > m_vecStart.x)
			pos.x -= m_fSpeed * DT;
		else
			repeat = false;
	}
	
	this->GetOwner()->SetPos(pos.x, pos.y);

}

void CLineMove::Render()
{
}

void CLineMove::Release()
{
}
