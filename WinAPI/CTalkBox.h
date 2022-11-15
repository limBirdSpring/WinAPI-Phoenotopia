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
	int* m_choose;//선택지유무
	int* m_choosing; //선택된 선택지


private :
	CImage* m_pTalkBox; 
	CImage* m_pChoose;//선택지이미지
	

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;


};