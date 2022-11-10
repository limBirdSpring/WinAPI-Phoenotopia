#pragma once
#include "WinAPI.h"

class CSceneManager;
class CEventManager;
class CCollisionManager;
class CUIManager;
class CGameObject;
class CSound;
class CImage;
class CImageObject;

class CScene
{
	friend CSceneManager;
	friend CEventManager;
	friend CCollisionManager;
	friend CUIManager;
protected:
	list<CGameObject*> m_listObj[(int)Layer::Size];

	CSound* pLoad_BGM;//�� �������
	CImage* m_pDoor = RESOURCE->LoadImg(L"InDoor", L"Image\\InDoor.png");

public:
	CScene();
	virtual ~CScene();

protected:
	UINT m_iTileSizeX;
	UINT m_iTileSizeY;

private :
	// �� �θ� ���� �Լ��� :
	// ���� �ִ� ��� ���ӿ�����Ʈ���� ����
	void SceneInit();
	void SceneEnter();
	void SceneUpdate();
	void ScenePhysicsUpdate();
	void SceneRender();
	void SceneExit();
	void SceneRelease();

	// ���������Լ�:
	// �Լ��� �߻�ȭ�Ͽ� ��üȭ���� ���� ��� �ν��Ͻ� ������ ����
	// ���� ��ӹ޾� ���������Լ����� ��üȭ���� ���� �ϼ���Ŵ
	virtual void Init() = 0;		// �ʱ�ȭ
	virtual void Enter() = 0;		// ����
	virtual void Update() = 0;		// ���ӷ��� ����
	virtual void Render() = 0;		// ����ǥ�� ����
	virtual void Exit() = 0;		// Ż��
	virtual void Release() = 0;		// ������

	void TileRender();

public:
	void LoadTile(const wstring& strPath);

protected :
	CImage* pMiddleImage;
	CImageObject* pImagePrev;
	CImageObject* pImageNext;
	CImageObject* pImageMiddle;

	CImage* pBackImage;
	CImageObject* pBImagePrev;
	CImageObject* pBImageNext;
	CImageObject* pBImageMiddle;

public :
	void LoadMiddleground(CImage* img); //�߰� ��� ���ε�
	void LoadBackground(CImage* img); //�� ��� ���ε�

	void MiddleGroundRender();
	void BackGroundRender();

protected:
	list<CGameObject*>& GetLayerObject(Layer layer);

	void AddGameObject(CGameObject* pGameObj);
	// ���������� ���ӿ�����Ʈ �ڷᱸ������ ������ ���ӿ�����Ʈ�� ã�Ƽ� �����ϴ� ����� ä������ ����
	// 1. ���ӿ�����Ʈ�� Ž���Ͽ� �����ϴ� ���� ��ȿ����
	// 2. ���������� ���ӿ�����Ʈ�� �����ϰ� �ִ� ���ӿ�����Ʈ�鿡�� �����ð��� �����
	// -> Update ������ ���������� ������Ʈ�� �������Ӹ� �����ϰ� ������������ ���۵� �� ������
	// void DeleteGameObject(CGameObject* pGameObj);
	void DeleteLayerObject(Layer layer);
	void DeleteAll();
};
