
#pragma once
#include "CScene.h"
#include "CFrog.h"


class CImage;


class CEnding :
	public CScene
{
public:
	CEnding();
	virtual ~CEnding();

private:
	CImage* m_pImage;
	int talk=0;
	wstring m_strDialogue = L"";

private:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;
};
