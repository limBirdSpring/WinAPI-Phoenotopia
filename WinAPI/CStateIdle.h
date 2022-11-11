#pragma once
#include "CPlayerState.h"

class CPlayer;

class CStateIdle :
    public CPlayerState
{
public :
    CStateIdle(CPlayer* player) { pPlayer = player; }
    virtual ~CStateIdle();
private :


private :
    void Init() override;
    void Update()  override;
    void Render()  override;
    void Release()  override;
};

