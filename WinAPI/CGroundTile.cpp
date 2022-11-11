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
	if (pOther->GetObjName() == L"�÷��̾�" || pOther->GetObjName() == L"������")
	{
		int ground = pOther->GetOwner()->GetGround();
		pOther->GetOwner()->SetGround(++ground);
	}
}

void CGroundTile::OnCollisionStay(CCollider* pOther)
{

	// ��Ÿ�ϰ� �浹���� ��� ó��
}

void CGroundTile::OnCollisionExit(CCollider* pOther)
{
	if (pOther->GetObjName() == L"�÷��̾�" || pOther->GetObjName() == L"������")
	{
		int ground = pOther->GetOwner()->GetGround();
		pOther->GetOwner()->SetGround(--ground);
	}
}
