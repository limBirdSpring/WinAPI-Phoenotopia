#include "framework.h"
#include "CGroundTile.h"

#include "CResourceManager.h"
#include "CRenderManager.h"
#include "CCollider.h"
#include "CCollisionManager.h"
#include "CGameObject.h"

CGroundTile::CGroundTile()
{
}

CGroundTile::~CGroundTile()
{
}

void CGroundTile::Init()
{
	CTile::Init();

	AddCollider(ColliderType::Rect,
		Vector(CTile::TILESIZE, CTile::TILESIZE),
		Vector(CTile::TILESIZE / 2, CTile::TILESIZE / 2));
}

void CGroundTile::Update()
{
	CTile::Update();
}

void CGroundTile::Render()
{
	CTile::Render();

	ComponentRender();
}

void CGroundTile::Release()
{
	CTile::Release();
}

void CGroundTile::OnCollisionEnter(CCollider* pOther)
{
	if (pOther->GetObjName() == L"플레이어" || pOther->GetObjName() == L"아이템")
	{
		int ground = pOther->GetOwner()->GetGround();
		pOther->GetOwner()->SetGround(++ground);
	}
}

void CGroundTile::OnCollisionStay(CCollider* pOther)
{

	// 땅타일과 충돌했을 경우 처리
}

void CGroundTile::OnCollisionExit(CCollider* pOther)
{
	if (pOther->GetObjName() == L"플레이어" || pOther->GetObjName() == L"아이템")
	{
		int ground = pOther->GetOwner()->GetGround();
		pOther->GetOwner()->SetGround(--ground);
	}
}
