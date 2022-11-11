
#pragma once
#include "CPlayerState.h"

class CPlayer;

class CStateAttackReady :
    public CPlayerState
{
public:
    CStateAttackReady(CPlayer* player) { pPlayer = player; }
    virtual ~CStateAttackReady();
private:

private:
    void Init() override;
    void Update()  override;
    void Render()  override;
    void Release()  override;
};

