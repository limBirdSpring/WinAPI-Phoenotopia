#pragma once
#include "CScene.h"

class CPlayer;
class CImage;

class CSceneGym :
	public CScene
{
public:
	CSceneGym();
	virtual ~CSceneGym();

private:
	CPlayer* pPlayer;
	CImage* m_pImage;
	bool isTeacher = false;

private:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;
};
