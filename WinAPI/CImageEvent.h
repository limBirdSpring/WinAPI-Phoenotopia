
#pragma once
#include "CNPC.h"

class CImage;
class CPlayer;
class CImageBox;

class CImageEvent :
	public CNPC
{
public:
	CImageEvent(CPlayer* player);
	virtual ~CImageEvent();

	CImage* pEventImage;
	bool bIsImageRender;
	CImageBox* pImageBox;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;

	void Talk() {}

};