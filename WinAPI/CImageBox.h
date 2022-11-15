#pragma once
#include "CGameObject.h"

class CPlayer;

class CImageBox :
	public CGameObject
{
public:
	CImageBox();
	virtual ~CImageBox();

public:

	CImage* pEventImage;


private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;


};