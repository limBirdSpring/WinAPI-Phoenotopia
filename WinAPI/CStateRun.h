#pragma once
#include "CPlayerState.h"

class CPlayer;

class CStateRun :
    public CPlayerState
{
public:
    CStateRun(CPlayer* player) { pPlayer = player; }
    virtual ~CStateRun();
private:
    float dir = 0;

private:
    void Init() override;
    void Update()  override;
    void Render()  override;
    void Release()  override;
};

