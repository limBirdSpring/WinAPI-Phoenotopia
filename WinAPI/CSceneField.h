#pragma once
#include "CScene.h"

class CPlayer;
class CImage;

class CSceneField :
	public CScene
{
public:
	CSceneField();
	virtual ~CSceneField();

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
