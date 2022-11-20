#include "framework.h"
#include "CSceneLoad.h"
#include "CImageObject.h"

CSceneLoad::CSceneLoad()
{
	curCount = 0;
}

CSceneLoad::~CSceneLoad()
{
}

void CSceneLoad::Init()
{
	vLoadList.push_back(make_pair(L"Panselo", L"Sound\\Panselo.mp3"));
	vLoadList.push_back(make_pair(L"BossBattle", L"Sound\\BossBattle.mp3"));
	vLoadList.push_back(make_pair(L"Fun", L"Sound\\Fun.mp3"));
	vLoadList.push_back(make_pair(L"Title", L"Sound\\Title.mp3"));
	vLoadList.push_back(make_pair(L"DubbiForest", L"Sound\\DubbiForest.mp3"));
	vLoadList.push_back(make_pair(L"Attack", L"Sound\\Attack.mp3"));
	vLoadList.push_back(make_pair(L"Attack2", L"Sound\\Attack2.mp3"));
	vLoadList.push_back(make_pair(L"AttackSlow", L"Sound\\AttackSlow.mp3"));
	vLoadList.push_back(make_pair(L"Damage", L"Sound\\Damage.mp3"));
	vLoadList.push_back(make_pair(L"Bee", L"Sound\\Bee.mp3"));

	vLoadList.push_back(make_pair(L"BoxDamage", L"Sound\\BoxDamage.ogg"));
	vLoadList.push_back(make_pair(L"BoxDead", L"Sound\\BoxDead.ogg"));
	vLoadList.push_back(make_pair(L"Buy", L"Sound\\Buy.ogg"));
	vLoadList.push_back(make_pair(L"Choice", L"Sound\\Choice.ogg"));
	vLoadList.push_back(make_pair(L"Choice2", L"Sound\\Choice2.ogg"));
	vLoadList.push_back(make_pair(L"Ice", L"Sound\\Ice.ogg"));

	vLoadList.push_back(make_pair(L"Cursor", L"Sound\\Cursor.ogg"));
	vLoadList.push_back(make_pair(L"CriticalReady", L"Sound\\CriticalReady.ogg"));
	vLoadList.push_back(make_pair(L"Equip", L"Sound\\Equip.ogg"));
	vLoadList.push_back(make_pair(L"Heal", L"Sound\\Heal.ogg"));
	vLoadList.push_back(make_pair(L"Heal2", L"Sound\\Heal2.ogg"));

	vLoadList.push_back(make_pair(L"Close", L"Sound\\Close.ogg"));
	vLoadList.push_back(make_pair(L"Item", L"Sound\\Item.ogg"));
	vLoadList.push_back(make_pair(L"Marble", L"Sound\\Marble.ogg"));
	vLoadList.push_back(make_pair(L"Open", L"Sound\\Open.ogg"));
	vLoadList.push_back(make_pair(L"Shop", L"Sound\\Shop.ogg"));
	vLoadList.push_back(make_pair(L"PillarDoor", L"Sound\\PillarDoor.ogg"));
	vLoadList.push_back(make_pair(L"SlugDamage", L"Sound\\SlugDamage.ogg"));
	
	vLoadList.push_back(make_pair(L"Jump1", L"Sound\\Jump1.ogg"));
	vLoadList.push_back(make_pair(L"Jump2", L"Sound\\Jump2.ogg"));
	vLoadList.push_back(make_pair(L"Critical", L"Sound\\Critical.ogg"));
	vLoadList.push_back(make_pair(L"Critical2", L"Sound\\Critical2.ogg"));
	vLoadList.push_back(make_pair(L"Save", L"Sound\\Save.ogg"));
	vLoadList.push_back(make_pair(L"Frog", L"Sound\\Frog.ogg"));
	vLoadList.push_back(make_pair(L"Run", L"Sound\\Run.ogg"));
	vLoadList.push_back(make_pair(L"PlayerDamage", L"Sound\\PlayerDamage.ogg"));
	vLoadList.push_back(make_pair(L"PlayerDead", L"Sound\\PlayerDead.ogg"));
	vLoadList.push_back(make_pair(L"Coin", L"Sound\\Coin.mp3"));
	vLoadList.push_back(make_pair(L"PlayerRun", L"Sound\\PlayerRun.ogg"));
	vLoadList.push_back(make_pair(L"Dialogue", L"Sound\\Dialogue.mp3"));

	vLoadList.push_back(make_pair(L"BossDead", L"Sound\\BossDead.ogg"));
	vLoadList.push_back(make_pair(L"BossAppear", L"Sound\\BossAppear.mp3"));
	vLoadList.push_back(make_pair(L"Walk", L"Sound\\Walk.mp3"));

	vLoadList.push_back(make_pair(L"BossAttack", L"Sound\\BossAttack.ogg"));
	vLoadList.push_back(make_pair(L"BossAttack2", L"Sound\\BossAttack2.ogg"));
	vLoadList.push_back(make_pair(L"BossAttack3", L"Sound\\BossAttack3.ogg"));


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
	
	curCount++;
	
	RESOURCE->LoadSound(vLoadList.back().first, vLoadList.back().second);
	vLoadList.pop_back();
	if (vLoadList.size() != 0)
		percent = (curCount / vLoadList.size());
	else
		percent = 100;

	if (vLoadList.empty())
		CHANGESCENE(GroupScene::Title);
		
}

void CSceneLoad::Render()
{
	RENDER->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
	RENDER->Text(to_wstring(percent)+L"%", 1000, 675, 1080, 705,  Color(255,255,255,1), 30);
	RENDER->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
}

void CSceneLoad::Exit()
{
}

void CSceneLoad::Release()
{
}
