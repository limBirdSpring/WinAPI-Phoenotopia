#include "framework.h"
#include "CSceneManager.h"

#include "CScene.h"
#include "CSceneTitle.h"
#include "CSceneTileTool.h"
#include "CSceneStage01.h"
#include "CSceneForest.h"
#include "CSceneGailRoom.h"
#include "CSceneStore.h"
#include "CInventory.h"
#include "CSceneGym.h"
#include "CSceneField.h"
#include "CSceneBossMap.h"
#include "CSetUp.h"
#include "CPrinceForest.h"
#include "CSceneDead.h"
#include "CEnding.h"

CSceneManager::CSceneManager()
{
	m_pCurScene = nullptr;
}

CSceneManager::~CSceneManager()
{
}

void CSceneManager::Init()
{
	// TODO : ���ӿ� �ʿ��� �� �߰�
	// ���Ӿ����� �ڷᱸ���� �߰�
	CScene* pSceneTitle = new CSceneTitle();
	m_mapScene.insert(make_pair(GroupScene::Title, pSceneTitle));
	CSceneTileTool* pSceneTileTool = new CSceneTileTool;
	m_mapScene.insert(make_pair(GroupScene::TileTool, pSceneTileTool));
	CScene* pSceneStage01 = new CSceneStage01();
	m_mapScene.insert(make_pair(GroupScene::Stage01, pSceneStage01));
	CScene* pForest = new CSceneForest();
	m_mapScene.insert(make_pair(GroupScene::Forest, pForest));
	CScene* pGailRoom = new CSceneGailRoom();
	m_mapScene.insert(make_pair(GroupScene::GailRoom, pGailRoom));
	CScene* pStore = new CSceneStore();
	m_mapScene.insert(make_pair(GroupScene::Store, pStore));
	CScene* pGym = new CSceneGym();
	m_mapScene.insert(make_pair(GroupScene::Gym, pGym));
	CScene* pField = new CSceneField();
	m_mapScene.insert(make_pair(GroupScene::Field, pField));
	CScene* pBossMap = new CSceneBossMap();
	m_mapScene.insert(make_pair(GroupScene::BossMap, pBossMap));
	CScene* pPrinceForest = new CPrinceForest();
	m_mapScene.insert(make_pair(GroupScene::PrinceForest, pPrinceForest));
	CScene* pInventory = new CInventory();
	m_mapScene.insert(make_pair(GroupScene::Inventory, pInventory));
	CScene* pCSetUp = new CSetUp();
	m_mapScene.insert(make_pair(GroupScene::SetUp, pCSetUp));
	CScene* pCEnding = new CEnding();
	m_mapScene.insert(make_pair(GroupScene::Ending, pCEnding));
	CScene* pCSceneDead = new CSceneDead();
	m_mapScene.insert(make_pair(GroupScene::Dead, pCSceneDead));


	// ���Ӿ� �ڷᱸ���� ��ȸ�ϸ� ���� �ʱ�ȭ
	for (pair<GroupScene, CScene*> scene : m_mapScene)
	{
		scene.second->SceneInit();
	}

	// ���� ó������ �����ؾ��� ���Ӿ� ����
	m_pCurScene = pSceneTitle;
	m_pCurScene->SceneEnter();
}

void CSceneManager::Update()
{
	m_pCurScene->SceneUpdate();
	m_pCurScene->ScenePhysicsUpdate();
}

void CSceneManager::Render()
{
	m_pCurScene->SceneRender();
}

void CSceneManager::Release()
{
	// ���Ӿ� �ڷᱸ���� ��ȸ�ϸ� �����Ҵ�� ���� ����
	for (pair<GroupScene, CScene*> scene : m_mapScene)
	{
		scene.second->SceneRelease();
		delete scene.second;
	}
	
	// ��� �����Ҵ�� ���� �����ѵ� �ڷᱸ���� clear
	m_mapScene.clear();
}

void CSceneManager::ChangeScene(GroupScene scene)
{
	// �������� Exit, �������� Enter
	m_pCurScene->SceneExit();
	m_pCurScene = m_mapScene[scene];
	m_pCurScene->SceneEnter();
}

void CSceneManager::ResetScene()
{
	map<GroupScene, CScene*>::iterator scene = m_mapScene.begin();


	for (;scene != --m_mapScene.end();scene++)
	{
		(*scene).second->SceneRelease();
		(*scene).second->SceneInit();
	}


}

CScene* CSceneManager::GetCurScene()
{
	return m_pCurScene;
}
