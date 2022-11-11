#pragma once
#include "CPlayerState.h"

class CPlayer;

class CStateWalk :
    public CPlayerState
{
public:
    CStateWalk(CPlayer* player);
    virtual ~CStateWalk();
private:
    CPlayer* pPlayer;

private:
    void Init() override;
    void Update()  override;
    void Render()  override;
    void Release()  override;
};

