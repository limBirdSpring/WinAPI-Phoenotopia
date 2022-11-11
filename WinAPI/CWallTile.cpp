#include "framework.h"
#include "CWallTile.h"

#include "CResourceManager.h"
#include "CRenderManager.h"
#include "CCollider.h"
#include "CCollisionManager.h"
#include "CGameObject.h"
#include "CPlayer.h"
CWallTile::CWallTile()
{
	
	m_strName = L"벽";
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
		
	}
}

void CWallTile::OnCollisionStay(CCollider* pOther)
{
	if (pOther->GetObjName() == L"플레이어")
	{
		// 플레이어가 충돌 중일 경우 밀어내기 연산
		CPlayer* pPlayer = static_cast<CPlayer*>(pOther->GetOwner());

		dir = GetCollisionDir(pOther);

		switch (GetCollisionDir(pOther))
		{
		case CollisionDir::Up:
		{
			pPlayer->SetPos(
				pPlayer->GetPos().x,
				GetCollider()->GetPos().y
				- (GetCollider()->GetScale().y + pOther->GetScale().y) * 0.5f + offset
				- pOther->GetOffsetPos().y
			);
		}
		break;

		case CollisionDir::Down:
		{
			pPlayer->SetPos(
				pPlayer->GetPos().x,
				GetCollider()->GetPos().y
				+ (GetCollider()->GetScale().y + pOther->GetScale().y) * 0.5f - offset
				- pOther->GetOffsetPos().y
			);
		}
		break;

		case CollisionDir::Left:
		{
			pPlayer->SetPos(
				GetCollider()->GetPos().x
				- (GetCollider()->GetScale().x + pOther->GetScale().x) * 0.5f + offset
				- pOther->GetOffsetPos().x,
				pPlayer->GetPos().y
			);
		}
		break;

		case CollisionDir::Right:
		{
			pPlayer->SetPos(
				GetCollider()->GetPos().x
				+ (GetCollider()->GetScale().x + pOther->GetScale().x) * 0.5f - offset
				- pOther->GetOffsetPos().x,
				pPlayer->GetPos().y
			);
		}
		break;
		}
	}
	
}

void CWallTile::OnCollisionExit(CCollider* pOther)
{
	if (pOther->GetObjName() == L"플레이어")
	{
	}
}

struct ColliderInfo
{
	Vector pos;
	Vector scale;

	float left;
	float right;
	float up;
	float down;

	ColliderInfo(Vector pos, Vector scale)
	{
		this->pos = pos;
		this->scale = scale;

		left = pos.x - scale.x * 0.5f;
		right = pos.x + scale.x * 0.5f;
		up = pos.y - scale.y * 0.5f;
		down = pos.y + scale.y * 0.5f;
	}
};

typename CWallTile::CollisionDir CWallTile::GetCollisionDir(CCollider* pOther)
{
	ColliderInfo obj = ColliderInfo(GetCollider()->GetPos(), GetCollider()->GetScale());
	ColliderInfo other = ColliderInfo(pOther->GetPos(), pOther->GetScale());

	if (((obj.scale.x + other.scale.x) * 0.5f - abs(obj.pos.x - other.pos.x) < offset * 4
		&& ((obj.scale.y + other.scale.y) * 0.5f - abs(obj.pos.y - other.pos.y)) < offset * 4))
	{
		return CollisionDir::None;
	}
	else if (((obj.scale.x + other.scale.x) * 0.5f - abs(obj.pos.x - other.pos.x))
		< (obj.scale.y + other.scale.y) * 0.5f - abs(obj.pos.y - other.pos.y))
	{
		if (obj.pos.x > other.pos.x && obj.left < other.right - offset)
			return CollisionDir::Left;
		if (obj.pos.x < other.pos.x && obj.right > other.left + offset)
			return CollisionDir::Right;
	}
	else
	{
		if (obj.pos.y > other.pos.y && obj.up < other.down - offset)
			return CollisionDir::Up;
		if (obj.pos.y < other.pos.y && obj.down > other.up + offset)
			return CollisionDir::Down;
	}

	return CollisionDir::None;
}