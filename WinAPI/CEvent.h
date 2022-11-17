#pragma once
#include "CGameObject.h"
#include "framework.h"

class CImage;
class CPlayer;
class CTalkBox;

class CEvent :
	public CGameObject
{
public:
	CEvent();
	virtual ~CEvent();

private:
	virtual void Talk() = 0;

protected:
	wstring m_strDialogue;
	int talk; //��ȭ����

	int changeTalkTopic; // ���� ��ȭ�� �Ѿ��


	int m_choose;//����������
	int m_choosing; //���õ� ������


	CTalkBox* pTalkBox;
	CPlayer* pPlayer;


private:
	virtual void Init() override = 0;
	virtual void Update() override = 0;
	virtual void Render() override = 0;
	virtual void Release() override = 0;

};