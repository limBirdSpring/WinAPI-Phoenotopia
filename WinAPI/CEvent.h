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
	int talk; //대화순서

	int changeTalkTopic; // 다음 대화로 넘어가기


	int m_choose;//선택지유무
	int m_choosing; //선택된 선택지


	CTalkBox* pTalkBox;
	CPlayer* pPlayer;

	float coolTime;


private:
	virtual void Init() override = 0;
	virtual void Update() override = 0;
	virtual void Render() override = 0;
	virtual void Release() override = 0;

};