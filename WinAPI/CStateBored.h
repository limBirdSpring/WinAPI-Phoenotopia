#pragma once
#include "CPlayerState.h"

class CPlayer;

class CStateBored :
    public CPlayerState
{
public:
    CStateBored(CPlayer* player);
    virtual ~CStateBored();
private:


private:
    void Init() override;
    void Update()  override;
    void Render()  override;
    void Release()  override;
};

