#pragma once
#include "CPlayerState.h"

class CPlayer;

class CStateDamage :
    public CPlayerState
{
public:
    CStateDamage(CPlayer* player) { pPlayer = player; }
    virtual ~CStateDamage();
private:
    CPlayer* pPlayer;

private:
    void Init() override;
    void Update()  override;
    void Render()  override;
    void Release()  override;
};

