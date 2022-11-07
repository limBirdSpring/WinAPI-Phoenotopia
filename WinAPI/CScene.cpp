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
	// 씬 내에 모든 게임오브젝트 초기화
	for (int layer = 0; layer < (int)Layer::Size; layer++)
	{
		for (CGameObject* pGameObject : m_listObj[layer])
		{
			pGameObject->GameObjectInit();
		}
	}

	// 상속한 자식 초기화
	Init();
}

void CScene::SceneEnter()
{
	// 이전 씬의 카메라 상황을 초기화하고 카메라의 위치를 초기 위치로
	// 씬의 카메라 시작위치가 초기 위치가 아닌경우 씬의 Enter에서 위치를 설정하여 목표위치가 덮어씀
	CAMERA->SetTargetObj(nullptr);
	CAMERA->SetTargetPos(Vector(WINSIZEX * 0.5f, WINSIZEY * 0.5f));
	Enter();
}

void CScene::SceneUpdate()
{
	// 씬 내에 삭제해도 안전한 게임오브젝트를 삭제
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

	// 씬 내에 모든 게임오브젝트 로직갱신
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

	// 상속한 자식 로직갱신
	Update();
}

void CScene::ScenePhysicsUpdate()
{
	// 씬 내에 모든 게임오브젝트 물리처리 진행
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
	// 씬 내에 모든 게임오브젝트 표현갱신
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


	// 상속한 자식 표현갱신
	Render();
}

void CScene::SceneExit()
{
	Exit();
}

void CScene::SceneRelease()
{
	// 씬 내에 모든 게임오브젝트 마무리
	for (int layer = 0; layer < (int)Layer::Size; layer++)
	{
		for (CGameObject* pGameObject : m_listObj[layer])
		{
			pGameObject->GameObjectRelease();
			delete pGameObject;
		}
		m_listObj[layer].clear();
	}

	// 상속한 자식 마무리
	Release();
}

void CScene::TileRender()
{
	// 게임 화면에 표시되지 않는 타일은 랜더링을 진행하지 않음
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

		// TODO : 타일 타입에 따른 생성
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

			CImageObject* temp;
			temp = pImageNext;
			pImageNext = pImagePrev;
			pImagePrev = pImageMiddle;
			pImageMiddle = temp;
		}
		else if (pImageNext->GetPos().x > endCameraPos.x)
		{
			pImageNext->SetPos(pImagePrev->GetPos().x - pMiddleImage->GetWidth(), 0);

			CImageObject* temp;
			temp = pImagePrev;
			pImagePrev = pImageNext;
			pImageNext = pImageMiddle;
			pImageMiddle = temp;

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

			CImageObject* temp;
			temp = pBImageNext;
			pBImageNext = pBImagePrev;
			pBImagePrev = pBImageMiddle;
			pBImageMiddle = temp;


		}
		else if (pBImageNext->GetPos().x > endCameraPos.x)
		{
			pBImageNext->SetPos(pBImagePrev->GetPos().x - pBackImage->GetWidth(), 0);

			CImageObject* temp;
			temp = pBImagePrev;
			pBImagePrev = pBImageNext;
			pBImageNext = pBImageMiddle;
			pBImageMiddle = temp;


		}
	}
}


list<CGameObject*>& CScene::GetLayerObject(Layer layer)
{
	return m_listObj[(int)layer];
}

void CScene::AddGameObject(CGameObject* pGameObj)
{
	// 새로운 게임오브젝트 추가 및 초기화
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
