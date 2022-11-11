#pragma once
#include "CPlayerState.h"

class CPlayer;
class CStateFall :
    public CPlayerState
{
public:
    CStateFall(CPlayer* player) { pPlayer = player; }
    virtual ~CStateFall();
private:
    CPlayer* pPlayer;
    float coolTime;

private:
    void Init() override;
    void Update()  override;
    void Render()  override;
    void Release()  override;
};

