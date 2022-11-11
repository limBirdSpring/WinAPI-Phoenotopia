
#pragma once
#include "CPlayerState.h"

class CPlayer;

class CStateDown :
    public CPlayerState
{
public:
    CStateDown(CPlayer* player) { pPlayer = player; }
    virtual ~CStateDown();
private:
    CPlayer* pPlayer;

private:
    void Init() override;
    void Update()  override;
    void Render()  override;
    void Release()  override;
};

