#pragma once
#include "CGameObject.h"
#include "framework.h"
#include "CAnimator.h"

class CImage;
class CScene;

class CDamageNumber :
	public CGameObject
{
public:
	CDamageNumber();
	virtual ~CDamageNumber();

	int m_damage;

private:

	float coolTime;

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;


};
