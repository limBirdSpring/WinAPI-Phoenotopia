
#pragma once
#include "CPlayerState.h"

class CPlayer;
class CStateDownJump :
    public CPlayerState
{
public:
    CStateDownJump(CPlayer* player) { pPlayer = player; }
    virtual ~CStateDownJump();
private:
    CPlayer* pPlayer;
    float coolTime;

private:
    void Init() override;
    void Update()  override;
    void Render()  override;
    void Release()  override;
};

