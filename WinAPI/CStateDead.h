#pragma once
#include "CPlayerState.h"

class CPlayer;

class CStateDead :
    public CPlayerState
{
public:
    CStateDead(CPlayer* player);
    virtual ~CStateDead();
private:


private:
    void Init() override;
    void Update()  override;
    void Render()  override;
    void Release()  override;
};

