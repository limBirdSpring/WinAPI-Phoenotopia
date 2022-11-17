
#pragma once
#include "CPlayerState.h"

class CPlayer;

class CStateWonder :
    public CPlayerState
{
public:
    CStateWonder(CPlayer* player);
    virtual ~CStateWonder();
private:


private:
    void Init() override;
    void Update()  override;
    void Render()  override;
    void Release()  override;
};

