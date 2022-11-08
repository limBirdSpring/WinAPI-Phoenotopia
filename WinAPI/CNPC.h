#pragma once
#include "CGameObject.h"
#include "framework.h"

class CImage;

class CNPC :
	public CGameObject
{
public:
	CNPC();
	virtual ~CNPC();

private :
	virtual void Talk() = 0;

protected:
	wstring m_strDialogue;
	int talk; //대화순서
	CImage* m_pTalkBox;

private:
	virtual void Init() override = 0;
	virtual void Update() override = 0;
	virtual void Render() override = 0;
	virtual void Release() override = 0;

	virtual void OnCollisionStay(CCollider* pOtherCollider) override = 0;
};