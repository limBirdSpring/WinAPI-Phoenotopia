#pragma once
#include "CScene.h"

class CPlayer;
class CImage;

class CSceneCave :
	public CScene
{
public:
	CSceneCave();
	virtual ~CSceneCave();

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
