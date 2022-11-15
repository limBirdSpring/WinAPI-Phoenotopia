#pragma once
#include "CGameObject.h"

class CImage;

class CFrontImage :
	public CGameObject
{
public:
	CFrontImage();
	virtual ~CFrontImage();

private:
	CImage* m_pImage;

	float m_fSpeed;

public:
	CImage* GetIamge();
	void SetImage(CImage* pImage);

	void SetSpeed(float speed) { m_fSpeed = speed; }
	float GetSpeed() { return m_fSpeed; }


private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

