
#pragma once
#include "CPlayerState.h"

class CPlayer;

class CStateAttack2 :
    public CPlayerState
{
public:
    CStateAttack2(CPlayer* player) { pPlayer = player; }
    virtual ~CStateAttack2();
private:
    CPlayer* pPlayer;

private:
    void Init() override;
    void Update()  override;
    void Render()  override;
    void Release()  override;
};

