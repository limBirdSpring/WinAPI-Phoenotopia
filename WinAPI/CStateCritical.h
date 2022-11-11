#pragma once
#include "CPlayerState.h"

class CPlayer;

class CStateCritical :
    public CPlayerState
{
public:
    CStateCritical(CPlayer* player) { pPlayer = player; }
    virtual ~CStateCritical();
private:
    CPlayer* pPlayer;

private:
    void Init() override;
    void Update()  override;
    void Render()  override;
    void Release()  override;
};

