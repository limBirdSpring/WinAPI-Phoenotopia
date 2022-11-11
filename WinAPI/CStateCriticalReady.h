#pragma once
#include "CPlayerState.h"

class CPlayer;

class CStateCriticalReady :
    public CPlayerState
{
public:
    CStateCriticalReady(CPlayer* player) { pPlayer = player; }
    virtual ~CStateCriticalReady();
private:
    CPlayer* pPlayer;

private:
    void Init() override;
    void Update()  override;
    void Render()  override;
    void Release()  override;
};

