#pragma once
#include "CScene.h"
#include "CFrog.h"

class CPlayer;
class CImage;


class CPrinceForest :
	public CScene
{
public:
	CPrinceForest();
	virtual ~CPrinceForest();

private:
	CPlayer* pPlayer;
	CImage* m_pImage;

	float coolTime;

private:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;
};
