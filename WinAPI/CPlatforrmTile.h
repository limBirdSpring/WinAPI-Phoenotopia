#pragma once
#include "CTile.h"

class CPlatformTile : public CTile
{
public:
	CPlatformTile();
	virtual ~CPlatformTile();

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;


private:
	void OnCollisionEnter(CCollider* pOther) override;
	void OnCollisionStay(CCollider* pOther) override;
	void OnCollisionExit(CCollider* pOther) override;
};


