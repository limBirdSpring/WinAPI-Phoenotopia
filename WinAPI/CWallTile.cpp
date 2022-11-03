#include "framework.h"
#include "CWallTile.h"

#include "CResourceManager.h"
#include "CRenderManager.h"
#include "CCollider.h"
#include "CCollisionManager.h"
#include "CGameObject.h"

CWallTile::CWallTile()
{
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
		Vector pos = pOther->GetOwner()->GetPos();

		if (pos.x > this->GetPos().x)
			pOther->GetOwner()->SetPos(this->GetPos().x + this->GetScale().x + (pOther->GetOwner()->GetScale().x * 0.5), pos.y);
		if (pos.x < this->GetPos().x)
			pOther->GetOwner()->SetPos(this->GetPos().x - (pOther->GetOwner()->GetScale().x * 0.5), pos.y);
		if (pos.y < this->GetPos().y)
			pOther->GetOwner()->SetPos(pos.x, this->GetPos().y - (pOther->GetOwner()->GetScale().y * 0.5));
	}
}

void CWallTile::OnCollisionStay(CCollider* pOther)
{

	// 땅타일과 충돌했을 경우 처리
}

void CWallTile::OnCollisionExit(CCollider* pOther)
{

}
