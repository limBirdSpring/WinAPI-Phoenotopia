#pragma once
#include "CScene.h"
#include "CFrog.h"

class CPlayer;
class CImage;


class CSceneDead :
	public CScene
{
public:
	CSceneDead();
	virtual ~CSceneDead();

private:
	CPlayer* pPlayer;
	CImage* m_pImage;


private:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;
};
