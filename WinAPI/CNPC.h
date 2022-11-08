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
	int talk; //��ȭ����
	CImage* m_pTalkBox;
	int m_choose;//����������
	int m_choosing; //���õ� ������
	CImage* m_pChoose;//�������̹���

private:
	virtual void Init() override = 0;
	virtual void Update() override = 0;
	virtual void Render() override = 0;
	virtual void Release() override = 0;

	virtual void OnCollisionStay(CCollider* pOtherCollider) override = 0;
};