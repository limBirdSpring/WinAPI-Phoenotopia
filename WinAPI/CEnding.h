
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


private:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;
};
