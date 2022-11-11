#pragma once
#include "CPlayerState.h"

class CPlayer;

class CStateTalk :
    public CPlayerState
{
public:
    CStateTalk(CPlayer* player);
    virtual ~CStateTalk();
private:


private:
    void Init() override;
    void Update()  override;
    void Render()  override;
    void Release()  override;
};

