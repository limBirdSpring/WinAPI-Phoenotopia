#pragma once
#include "CScene.h"

class CPlayer;
class CImage;

class CSceneGailRoom :
	public CScene
{
public:
	CSceneGailRoom();
	virtual ~CSceneGailRoom();

private:
	CPlayer* pPlayer;
	CImage* m_pImage;

	float coolTime = 0;

private:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;
};
