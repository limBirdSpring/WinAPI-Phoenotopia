#include "framework.h"
#include "CWallTile.h"

#include "CResourceManager.h"
#include "CRenderManager.h"
#include "CCollider.h"
#include "CCollisionManager.h"
#include "CGameObject.h"

CWallTile::CWallTile()
{
	wall = false;
}

CWallTile::~CWallTile()
{
}

void CWallTile::Init()
{
	CTile::Init();

	AddCollider(ColliderType::Rect,
		Vector(CTile::TILESIZE, CTile::TILESIZE),
		Vector(CTile::TILESIZE / 2, CTile::TILESIZE / 2));
}

void CWallTile::Update()
{
	CTile::Update();
}

void CWallTile::Render()
{
	CTile::Render();

	ComponentRender();
}

void CWallTile::Release()
{
	CTile::Release();
}

void CWallTile::OnCollisionEnter(CCollider* pOther)
{
	if (pOther->GetObjName() == L"플레이어")
	{
		wall = true;
	}
}

void CWallTile::OnCollisionStay(CCollider* pOther)
{
	
	// 땅타일과 충돌했을 경우 처리
}

void CWallTile::OnCollisionExit(CCollider* pOther)
{
	if (pOther->GetObjName() == L"플레이어")
	{
		wall = false;
	}
}
