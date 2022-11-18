#pragma once
#include "CPlayerState.h"

class CPlayer;

class CStateMove :
    public CPlayerState
{
public:
    CStateMove(CPlayer* player) { pPlayer = player; }
    virtual ~CStateMove();
private:


private:
    void Init() override;
    void Update()  override;
    void Render()  override;
    void Release()  override;
};

