#pragma once
#include "CPlayerState.h"

class CPlayer;

class CStatePush :
    public CPlayerState
{
public:
    CStatePush(CPlayer* player) { pPlayer = player; }
    virtual ~CStatePush();
private:


private:
    void Init() override;
    void Update()  override;
    void Render()  override;
    void Release()  override;
};

