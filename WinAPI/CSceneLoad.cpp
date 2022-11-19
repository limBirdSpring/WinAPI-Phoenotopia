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
	vLoadList.push_back(make_pair(L"Damage", L"Sound\\Damage.mp3"));

	vLoadList.push_back(make_pair(L"BoxDamage", L"Sound\\BoxDamage.ogg"));
	vLoadList.push_back(make_pair(L"BoxDead", L"Sound\\BoxDead.ogg"));
	vLoadList.push_back(make_pair(L"Buy", L"Sound\\Buy.ogg"));
	vLoadList.push_back(make_pair(L"Choice", L"Sound\\Choice.ogg"));

	vLoadList.push_back(make_pair(L"Cursor", L"Sound\\Cursor.ogg"));
	vLoadList.push_back(make_pair(L"CriticalReady", L"Sound\\CriticalReady.ogg"));
	vLoadList.push_back(make_pair(L"Equip", L"Sound\\Equip.ogg"));
	vLoadList.push_back(make_pair(L"Heal", L"Sound\\Heal.ogg"));
	vLoadList.push_back(make_pair(L"Heal2", L"Sound\\Heal.ogg"));

	vLoadList.push_back(make_pair(L"Close", L"Sound\\Close.ogg"));
	vLoadList.push_back(make_pair(L"Item", L"Sound\\Item.ogg"));
	vLoadList.push_back(make_pair(L"Marble", L"Sound\\Marble.ogg"));
	vLoadList.push_back(make_pair(L"Open", L"Sound\\Open.ogg"));
	vLoadList.push_back(make_pair(L"Shop", L"Sound\\Shop.ogg"));
	vLoadList.push_back(make_pair(L"PillarDoor", L"Sound\\PillarDoor.ogg"));
	vLoadList.push_back(make_pair(L"SlugDamage", L"Sound\\SlugDamage.ogg"));


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
