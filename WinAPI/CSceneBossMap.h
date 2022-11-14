#pragma once
#include "CScene.h"
#include "CFrog.h"

class CPlayer;
class CImage;


class CSceneBossMap :
	public CScene
{
public:
	CSceneBossMap();
	virtual ~CSceneBossMap();

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
