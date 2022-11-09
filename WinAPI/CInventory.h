#pragma once
#include "CScene.h"

class CPlayer;
class CImage;
class CSelect;

class CInventory :
	public CScene
{
public:
	CInventory();
	virtual ~CInventory();

private:
	CImage* m_pImage;
	CSelect* m_pSelect;

	int selectItem;



private:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;
};
