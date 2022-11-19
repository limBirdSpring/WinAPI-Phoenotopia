#include "framework.h"
#include "CSceneLoad.h"
#include "CImageObject.h"

CSceneLoad::CSceneLoad()
{
}

CSceneLoad::~CSceneLoad()
{
}

void CSceneLoad::Init()
{
	vLoadList.push_back(make_pair(L"Panselo", L"Sound\\Panselo.mp3"));
	vLoadList.push_back(make_pair(L"Title", L"Sound\\Title.mp3"));
	vLoadList.push_back(make_pair(L"DubbiForest", L"Sound\\DubbiForest.mp3"));
	vLoadList.push_back(make_pair(L"Attack", L"Sound\\Attack.mp3"));
	vLoadList.push_back(make_pair(L"Attack2", L"Sound\\Attack2.mp3"));

	pLoad_Screen = RESOURCE->LoadImg(L"Load_Screen", L"Image\\Load_Screen.png");
	pTitleObject = new CImageObject;
	pTitleObject->SetImage(pLoad_Screen);
	pTitleObject->SetPos(0, 0);
	AddGameObject(pTitleObject);
}

void CSceneLoad::Enter()
{
	CAMERA->ZoomInOut(1);

	

	
}

void CSceneLoad::Update()
{
	
	//curCount++;
	
	RESOURCE->LoadSound(vLoadList.back().first, vLoadList.back().second);
	vLoadList.pop_back();
	//float percent = curCount / vLoadList.size();

	//if (vLoadList.empty())

	//for (int i = 0; i < vLoadList.size(); i++)
	//{
	//	RESOURCE->LoadSound(vLoadList[i].first, vLoadList[i].second);
	//}
	//
	if (vLoadList.empty())
		CHANGESCENE(GroupScene::Title);
		
}

void CSceneLoad::Render()
{
	
}

void CSceneLoad::Exit()
{
}

void CSceneLoad::Release()
{
}
