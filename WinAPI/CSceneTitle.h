#pragma once
#include "CScene.h"

class CImage;
class CSound;
class CImageObject;
class CFrontImage;

class CSceneTitle : public CScene
{
public:
	CSceneTitle();
	virtual ~CSceneTitle();

private:

	CImage* pLoad_Screen;
	CImage* pTitle;
	CImageObject* pTitleObject;
	CFrontImage* pTitle_Front;
	CSound* pSe;


	float coolTime;

	float textAlpha;
	int textAlphaDir;


	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;
};
