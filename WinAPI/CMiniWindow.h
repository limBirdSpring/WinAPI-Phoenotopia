#pragma once
#include "CGameObject.h"
#include "framework.h"
#include "CInventory.h"

class CImage;
class CScene;

class CMiniWindow :
	public CGameObject
{
	friend CInventory;

public:
	CMiniWindow();
	virtual ~CMiniWindow();

private:

	int select;
	int selectItem;

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;


};