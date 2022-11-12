#include "framework.h"
#include "CMonsterState.h"

CMonsterState::CMonsterState()
{
	coolTime = 0;
	srand(time(NULL));
}

CMonsterState::~CMonsterState()
{
}
