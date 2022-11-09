#pragma once
#include "CGameObject.h"
#include "framework.h"
#include "CAnimator.h"

class CImage;
class CScene;

class CSelect :
	public CGameObject
{
public:
	CSelect();
	virtual ~CSelect();

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;


};