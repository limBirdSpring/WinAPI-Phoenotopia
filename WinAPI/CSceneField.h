#pragma once
#include "CScene.h"
#include "CFrog.h"

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
	vector<CFrog*> m_vFrog;


private:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;
};
