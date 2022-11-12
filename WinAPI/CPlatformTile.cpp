#include "framework.h"
#include "CPlatformTile.h"

#include "CResourceManager.h"
#include "CRenderManager.h"
#include "CCollider.h"
#include "CCollisionManager.h"
#include "CGameObject.h"

CPlatformTile::CPlatformTile()
{
}

CPlatformTile::~CPlatformTile()
{
}

void CPlatformTile::Init()
{
	CTile::Init();

	AddCollider(ColliderType::Rect,
		Vector(CTile::TILESIZE, CTile::TILESIZE),
		Vector(CTile::TILESIZE / 2, CTile::TILESIZE / 2));
}

void CPlatformTile::Update()
{
	CTile::Update();
}

void CPlatformTile::Render()
{
	CTile::Render();

	ComponentRender();
}

void CPlatformTile::Release()
{
	CTile::Release();
}

void CPlatformTile::OnCollisionEnter(CCollider* pOther)
{
	
	//스케일이 아닌 콜리터 위치로 연산해야함.
	if (0 < pOther->GetOwner()->GetGravity() &&
		((pOther->GetOwner()->GetColliderPos().y) + (pOther->GetOwner()->GetScale().y * 0.5) < this->GetPos().y  + this->GetScale().y * 0.5))
	{
		pOther->GetOwner()->SetPos(pOther->GetOwner()->GetPos().x, 
			this->GetPos().y - ((pOther->GetOwner()->GetColliderPos().y - pOther->GetOwner()->GetPos().y) + pOther->GetOwner()->GetScale().y * 0.5)+1);

		
			int platform = pOther->GetOwner()->GetPlatform();
			pOther->GetOwner()->SetPlatform(++platform);

			int ground = pOther->GetOwner()->GetGround();
			pOther->GetOwner()->SetGround(++ground);

			pOther->GetOwner()->SetGravity(1);
	}
	
}

void CPlatformTile::OnCollisionStay(CCollider* pOther)
{


}

void CPlatformTile::OnCollisionExit(CCollider* pOther)
{
	
		if (pOther->GetOwner()->GetPlatform() != 0)
		{
			int platform = pOther->GetOwner()->GetPlatform();
			pOther->GetOwner()->SetPlatform(--platform);
		}
		if (pOther->GetOwner()->GetGround() != 0)
		{
			int ground = pOther->GetOwner()->GetGround();
			pOther->GetOwner()->SetGround(--ground);
		}
	
}
