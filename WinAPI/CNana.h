#pragma once
#include "CNPC.h"

class CNana :
	public CNPC
{
public:
	CNana(CPlayer* player);
	virtual ~CNana();

private:

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionStay(CCollider* pOtherCollider) override;

	void Talk();

};