#pragma once
#include "CScene.h"

class CPlayer;
class CImage;

class CSetUp :
	public CScene
{
public:
	CSetUp();
	virtual ~CSetUp();

private:
	CImage* m_pImage;
	CSound* pSe;

	int selectNum;



private:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;
};
