#include "framework.h"
#include "CMonster.h"

CMonster::CMonster()
{
	m_damageHp = 5;
	m_pAnimator = nullptr;
	m_pImage = nullptr;
}

CMonster::~CMonster()
{
}
