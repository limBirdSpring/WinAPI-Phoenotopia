#pragma once
#include "CPlayerState.h"

class CPlayer;

class CStateJump :
    public CPlayerState
{
public:
    CStateJump(CPlayer* player) { pPlayer = player; }
    virtual ~CStateJump();
private:

    bool farJump;

private:
    void Init() override;
    void Update()  override;
    void Render()  override;
    void Release()  override;
};

