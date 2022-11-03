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
	if (pOther->GetObjName() == L"�÷��̾�")
	{
		if (0 < pOther->GetOwner()->GetGravity() &&
			((pOther->GetOwner()->GetPos().y) + (pOther->GetOwner()->GetScale().y * 0.5) <= this->GetPos().y - (this->GetScale().y * 0.5) + 10))//�÷��̾ �ٴں��� ���� ��ġ�� �־����
		{
			int platform = pOther->GetOwner()->GetPlatform();
			pOther->GetOwner()->SetPlatform(++platform);

			int ground = pOther->GetOwner()->GetGround();
			pOther->GetOwner()->SetGround(++ground);
		}
	}
}

void CPlatformTile::OnCollisionStay(CCollider* pOther)
{


}

void CPlatformTile::OnCollisionExit(CCollider* pOther)
{
	if (pOther->GetObjName() == L"�÷��̾�")
	{
		if (pOther->GetOwner()->GetGround() != 0)
		{
			int platform = pOther->GetOwner()->GetPlatform();
			pOther->GetOwner()->SetPlatform(--platform);

			int ground = pOther->GetOwner()->GetGround();
			pOther->GetOwner()->SetGround(--ground);
		}
	}
}
