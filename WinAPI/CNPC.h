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
	int m_choose;//선택지유무
	int m_choosing; //선택된 선택지
	CImage* m_pChoose;//선택지이미지

private:
	virtual void Init() override = 0;
	virtual void Update() override = 0;
	virtual void Render() override = 0;
	virtual void Release() override = 0;

	virtual void OnCollisionStay(CCollider* pOtherCollider) override = 0;
};