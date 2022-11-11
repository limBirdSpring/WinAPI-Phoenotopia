#pragma once
#include "CPlayerState.h"

class CPlayer;

class CStateAttack :
    public CPlayerState
{
public:
    CStateAttack(CPlayer* player) { pPlayer = player; }
    virtual ~CStateAttack();
private:


private:
    void Init() override;
    void Update()  override;
    void Render()  override;
    void Release()  override;
};

