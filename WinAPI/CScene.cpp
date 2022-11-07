#include "framework.h"
#include "CScene.h"

#include "CCameraManager.h"
#include "CGameObject.h"
#include "CTile.h"
#include "CGroundTile.h"
#include "CPlatformTile.h"
#include "CWallTile.h"
#include "CImageObject.h"
#include "CImage.h"
#include "CResourceManager.h"
#include "CEventManager.h"

#include "CGameManager.h"

CScene::CScene()
{
	m_iTileSizeX = 0;
	m_iTileSizeY = 0;

	pImagePrev = nullptr;
	pImageNext=nullptr;
	pImageMiddle=nullptr;

	pBImagePrev = nullptr;
	pBImageNext = nullptr;
	pBImageMiddle = nullptr;
}


CScene::~CScene()
{
}

void CScene::SceneInit()
{
	// �� ���� ��� ���ӿ�����Ʈ �ʱ�ȭ
	for (int layer = 0; layer < (int)Layer::Size; layer++)
	{
		for (CGameObject* pGameObject : m_listObj[layer])
		{
			pGameObject->GameObjectInit();
		}
	}

	// ����� �ڽ� �ʱ�ȭ
	Init();
}

void CScene::SceneEnter()
{
	// ���� ���� ī�޶� ��Ȳ�� �ʱ�ȭ�ϰ� ī�޶��� ��ġ�� �ʱ� ��ġ��
	// ���� ī�޶� ������ġ�� �ʱ� ��ġ�� �ƴѰ�� ���� Enter���� ��ġ�� �����Ͽ� ��ǥ��ġ�� ���
	CAMERA->SetTargetObj(nullptr);
	CAMERA->SetTargetPos(Vector(WINSIZEX * 0.5f, WINSIZEY * 0.5f));
	Enter();
}

void CScene::SceneUpdate()
{
	// �� ���� �����ص� ������ ���ӿ�����Ʈ�� ����
	for (int layer = 0; layer < (int)Layer::Size; layer++)
	{
		m_listObj[layer].remove_if([](CGameObject* target)
			{
				if (target->GetSafeToDelete())
				{
					target->GameObjectRelease();
					delete target;
					return true;
				}
				else
					return false;
			});
	}

	// �� ���� ��� ���ӿ�����Ʈ ��������
	for (int layer = 0; layer < (int)Layer::Size; layer++)
	{
		for (CGameObject* pGameObject : m_listObj[layer])
		{
			if (pGameObject->GetReserveDelete())
				pGameObject->SetSafeToDelete();
			else
				pGameObject->GameObjectUpdate();
		}
	}

	// ����� �ڽ� ��������
	Update();
}

void CScene::ScenePhysicsUpdate()
{
	// �� ���� ��� ���ӿ�����Ʈ ����ó�� ����
	for (int layer = 0; layer < (int)Layer::Size; layer++)
	{
		for (CGameObject* pGameObject : m_listObj[layer])
		{
			pGameObject->GameObjectPhysicsUpdate();
		}
	}
}

void CScene::SceneRender()
{
	// �� ���� ��� ���ӿ�����Ʈ ǥ������
	for (int layer = 0; layer < (int)Layer::Size; layer++)
	{
		if ((int)Layer::MiddleGround == layer)
		{
			MiddleGroundRender();
			continue;
		}
		else if ((int)Layer::BackGround == layer)
		{
			BackGroundRender();
			continue;
		}
		else if ((int)Layer::Tile == layer)
		{
			TileRender();
			continue;
		}

		for (CGameObject* pGameObject : m_listObj[layer])
		{
			pGameObject->GameObjectRender();
		}
	}


	// ����� �ڽ� ǥ������
	Render();
}

void CScene::SceneExit()
{
	Exit();
}

void CScene::SceneRelease()
{
	// �� ���� ��� ���ӿ�����Ʈ ������
	for (int layer = 0; layer < (int)Layer::Size; layer++)
	{
		for (CGameObject* pGameObject : m_listObj[layer])
		{
			pGameObject->GameObjectRelease();
			delete pGameObject;
		}
		m_listObj[layer].clear();
	}

	// ����� �ڽ� ������
	Release();
}

void CScene::TileRender()
{
	// ���� ȭ�鿡 ǥ�õ��� �ʴ� Ÿ���� �������� �������� ����
	Vector vecCamLook = CAMERA->GetLookAt();
	Vector vecLeftTop = vecCamLook - Vector(WINSIZEX, WINSIZEY) / 2.f;

	int iLTX = (int)vecLeftTop.x / CTile::TILESIZE;
	int iLTY = (int)vecLeftTop.y / CTile::TILESIZE;
	int iRBX = (int)WINSIZEX / CTile::TILESIZE;
	int iRBY = (int)WINSIZEY / CTile::TILESIZE;

	for (CGameObject* pGameObject : m_listObj[(int)Layer::Tile])
	{
		CTile* pTile = (CTile*)pGameObject;
		if (pTile->GetTilePosX() > iLTX - 5 && pTile->GetTilePosX() < iLTX + iRBX + 5 &&
			pTile->GetTilePosY() > iLTY - 5 && pTile->GetTilePosY() < iLTY + iRBY + 5)
			pTile->Render();
	}
}

void CScene::LoadTile(const wstring& strPath)
{
	DeleteLayerObject(Layer::Tile);

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strPath.c_str(), L"rb");      // w : write, b : binary
	assert(pFile);

	UINT xCount = 0;
	UINT yCount = 0;
	UINT tileCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);
	fread(&tileCount, sizeof(UINT), 1, pFile);

	CTile loadTile;
	for (UINT i = 0; i < tileCount; i++)
	{
		loadTile.Load(pFile);

		// TODO : Ÿ�� Ÿ�Կ� ���� ����
		if (TypeTile::None == loadTile.GetType())
		{
			CTile* newTile = new CTile;
			newTile->SetTilePos(loadTile.GetTilePosX(), loadTile.GetTilePosY());
			newTile->SetTileIndex(loadTile.GetTileIndex());

			AddGameObject(newTile);
		}
		else if (TypeTile::Ground == loadTile.GetType())
		{
			CGroundTile* newTile = new CGroundTile;
			newTile->SetTilePos(loadTile.GetTilePosX(), loadTile.GetTilePosY());
			newTile->SetTileIndex(loadTile.GetTileIndex());

			AddGameObject(newTile);
		}
		else if (TypeTile::Platform == loadTile.GetType())
		{
			CPlatformTile* newTile = new CPlatformTile;
			newTile->SetTilePos(loadTile.GetTilePosX(), loadTile.GetTilePosY());
			newTile->SetTileIndex(loadTile.GetTileIndex());

			AddGameObject(newTile);
		}
		else if (TypeTile::Wall == loadTile.GetType())
		{
			CWallTile* newTile = new CWallTile;
			newTile->SetTilePos(loadTile.GetTilePosX(), loadTile.GetTilePosY());
			newTile->SetTileIndex(loadTile.GetTileIndex());

			AddGameObject(newTile);
		}
	}

	fclose(pFile);
}

void CScene::LoadMiddleground(CImage* img)
{
	pMiddleImage = img;

	pImageMiddle = new CImageObject;
	pImageMiddle->SetImage(img);
	pImageMiddle->SetPos(pImageMiddle->GetPos().x - pMiddleImage->GetWidth(), 0);
	AddGameObject(pImageMiddle);


	pImagePrev = new CImageObject;
	pImagePrev->SetImage(img);
	pImagePrev->SetPos(pImageMiddle->GetPos().x - pMiddleImage->GetWidth()+2, 0);
	AddGameObject(pImagePrev);

	
	pImageNext = new CImageObject;
	pImageNext->SetImage(img);
	pImageNext->SetPos(pImageMiddle->GetPos().x + pMiddleImage->GetWidth()-2, 0);
	AddGameObject(pImageNext);


}
void CScene::LoadBackground(CImage* img)
{
	pBackImage = img;

	pBImageMiddle = new CImageObject;
	pBImageMiddle->SetImage(img);
	pBImageMiddle->SetPos(pBImageMiddle->GetPos().x - pBackImage->GetWidth(), 0);
	AddGameObject(pBImageMiddle);


	pBImagePrev = new CImageObject;
	pBImagePrev->SetImage(img);
	pBImagePrev->SetPos(pBImageMiddle->GetPos().x - pBackImage->GetWidth() + 2, 0);
	AddGameObject(pBImagePrev);


	pBImageNext = new CImageObject;
	pBImageNext->SetImage(img);
	pBImageNext->SetPos(pBImageMiddle->GetPos().x + pBackImage->GetWidth() - 2, 0);
	AddGameObject(pBImageNext);
}

void CScene::MiddleGroundRender()
{

	if (pMiddleImage != nullptr)
	{
		
		pImageMiddle->SetPos((CAMERA->GetLookAt().x - (pMiddleImage->GetWidth() * 0.5))/2.5, 0);
		pImagePrev->SetPos(pImageMiddle->GetPos().x - pMiddleImage->GetWidth()+2, 0);
		pImageNext->SetPos(pImageMiddle->GetPos().x + pMiddleImage->GetWidth()-2, 0);

		Vector startCameraPos = Vector(CAMERA->GetLookAt().x - (WINSIZEX * 0.5), CAMERA->GetLookAt().y - (WINSIZEY * 0.5));
		Vector endCameraPos = Vector(CAMERA->GetLookAt().x + (WINSIZEX * 0.5), CAMERA->GetLookAt().y + (WINSIZEY * 0.5));

		if (pImagePrev->GetPos().x + pMiddleImage->GetWidth() < startCameraPos.x)
		{
			pImagePrev->SetPos(pImageNext->GetPos().x + pMiddleImage->GetWidth(), 0);

			CImageObject* temp = new CImageObject;
			temp = pImageNext;
			pImageNext = pImagePrev;
			pImagePrev = pImageMiddle;
			pImageMiddle = temp;

			//delete temp;
		}
		else if (pImageNext->GetPos().x > endCameraPos.x)
		{
			pImageNext->SetPos(pImagePrev->GetPos().x - pMiddleImage->GetWidth(), 0);

			CImageObject* temp = new CImageObject;
			temp = pImagePrev;
			pImagePrev = pImageNext;
			pImageNext = pImageMiddle;
			pImageMiddle = temp;

			//delete temp;
		}
	}
}

void CScene::BackGroundRender()
{
	if (pBackImage != nullptr)
	{

		pBImageMiddle->SetPos((CAMERA->GetLookAt().x - (pBackImage->GetWidth() * 0.5)) / 3, 0);
		pBImagePrev->SetPos(pBImageMiddle->GetPos().x - pBackImage->GetWidth() + 2, 0);
		pBImageNext->SetPos(pBImageMiddle->GetPos().x + pBackImage->GetWidth() - 2, 0);

		Vector startCameraPos = Vector(CAMERA->GetLookAt().x - (WINSIZEX * 0.5), CAMERA->GetLookAt().y - (WINSIZEY * 0.5));
		Vector endCameraPos = Vector(CAMERA->GetLookAt().x + (WINSIZEX * 0.5), CAMERA->GetLookAt().y + (WINSIZEY * 0.5));

		if (pBImagePrev->GetPos().x + pBackImage->GetWidth() < startCameraPos.x)
		{
			pBImagePrev->SetPos(pBImageNext->GetPos().x + pBackImage->GetWidth(), 0);

			CImageObject* temp = new CImageObject;
			temp = pBImageNext;
			pBImageNext = pBImagePrev;
			pBImagePrev = pBImageMiddle;
			pBImageMiddle = temp;

			//delete temp;
		}
		else if (pBImageNext->GetPos().x > endCameraPos.x)
		{
			pBImageNext->SetPos(pBImagePrev->GetPos().x - pBackImage->GetWidth(), 0);

			CImageObject* temp = new CImageObject;
			temp = pBImagePrev;
			pBImagePrev = pBImageNext;
			pBImageNext = pBImageMiddle;
			pBImageMiddle = temp;

			//delete temp;
		}
	}
}


list<CGameObject*>& CScene::GetLayerObject(Layer layer)
{
	return m_listObj[(int)layer];
}

void CScene::AddGameObject(CGameObject* pGameObj)
{
	// ���ο� ���ӿ�����Ʈ �߰� �� �ʱ�ȭ
	m_listObj[(int)pGameObj->GetLayer()].push_back(pGameObj);
	pGameObj->GameObjectInit();
}

void CScene::DeleteLayerObject(Layer layer)
{
	for (CGameObject* pObj : m_listObj[(int)layer])
	{
		delete pObj;
	}
	m_listObj[(int)layer].clear();
}

void CScene::DeleteAll()
{
	for (int i = 0; i < (UINT)Layer::Size; i++)
	{
		DeleteLayerObject((Layer)i);
	}
}
