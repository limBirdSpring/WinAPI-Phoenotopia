#pragma once
#include "CGameObject.h"

class CPlayer;

class CTalkBox :
	public CGameObject
{
public:
	CTalkBox();
	virtual ~CTalkBox();

public:
	wstring m_strDialogue;
	int* m_choose;//����������
	int* m_choosing; //���õ� ������


private :
	CImage* m_pTalkBox; 
	CImage* m_pChoose;//�������̹���
	

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;


};