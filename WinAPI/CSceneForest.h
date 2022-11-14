#pragma once
#include "CScene.h"
#include "CFrog.h"
#include "CBee.h"

class CPlayer;
class CImage;
class CBox;


class CSceneForest :
	public CScene
{
public:
	CSceneForest();
	virtual ~CSceneForest();

private:
	CPlayer* pPlayer;
	CImage* m_pImage;
	CBox* pBox;
	vector<CFrog*> m_vFrog;
	vector<CBee*> m_vBee;

private:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;
};
