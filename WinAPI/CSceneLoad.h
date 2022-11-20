#pragma once
#include "CScene.h"

class CImage;
class CSound;
class CImageObject;
class CFrontImage;

class CSceneLoad :
	public CScene
{
public:
	CSceneLoad();
	virtual ~CSceneLoad();

private:

	CImage* pLoad_Screen;
	CImage* pTitle;
	CImageObject* pTitleObject;
	CFrontImage* pTitle_Front;

	float coolTime;

	float textAlpha;
	int textAlphaDir;
	
	vector<pair<wstring, wstring>> vLoadList;
	UINT curCount;
	int percent;


	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;
};
