#include "framework.h"
#include "CPillarDoor.h"
#include "CMarble.h"
#include "CImage.h"
#include "CStatue.h"
#include "CPlayer.h"

CPillarDoor::CPillarDoor()
{
	m_layer = Layer::Door;
	m_vecScale = Vector(14, 80);
	m_fSpeed = 100;
}


CPillarDoor::~CPillarDoor()
{
}

void CPillarDoor::Init()
{
	
	m_pImage = RESOURCE->LoadImg(L"PillarDoor", L"Image\\PillarDoor.png");
	isSaveY = false;

	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 1, m_vecScale.y - 1), Vector(0, 0));
}

void CPillarDoor::Update()
{
	if (!isSaveY && m_vecPos.y > 0)
	{
		closeY = m_vecPos.y;
		openY = m_vecPos.y - m_pImage->GetHeight();
		isSaveY = true;
	}

	if (pMarble != nullptr)
	{
		if (pMarble->isMarbleOn)
		{
			if (m_vecPos.y < closeY)
				this->m_vecPos.y += DT * m_fSpeed;
		}
		else
		{
			if (m_vecPos.y > openY)
				this->m_vecPos.y -= DT * m_fSpeed;
		}
	}
	else if (pStatue != nullptr)
	{
		if (pStatue->isStatueOn)
		{
			if (m_vecPos.y < closeY)
				this->m_vecPos.y += DT * m_fSpeed;
		}
		else
		{
			if (m_vecPos.y > openY)
				this->m_vecPos.y -= DT * m_fSpeed;
		}
	}
	else
	{
		if (isClosed == true)
		{
			if (m_vecPos.y < closeY)
				this->m_vecPos.y += DT * m_fSpeed;
		}
		else
		{
			if (m_vecPos.y > openY)
				this->m_vecPos.y -= DT * m_fSpeed;
		}
	}
}

void CPillarDoor::Render()
{
	RENDER->Image(m_pImage, m_vecPos.x - m_pImage->GetWidth() * 0.5, m_vecPos.y - m_pImage->GetHeight() * 0.5, m_vecPos.x + m_pImage->GetWidth() *0.5, m_vecPos.y + m_pImage->GetHeight() * 0.5);
}

void CPillarDoor::Release()
{
}

void CPillarDoor::OnCollisionEnter(CCollider* pOtherCollider)
{
	pOtherCollider->GetOwner()->SetGravity(1);
}

void CPillarDoor::OnCollisionStay(CCollider* pOtherCollider)
{
	CPlayer* pPlayer = static_cast<CPlayer*>(pOtherCollider->GetOwner());

	dir = GetCollisionDir(pOtherCollider);

	switch (GetCollisionDir(pOtherCollider))
	{
	case CollisionDir::Up:
	{

		pPlayer->SetPos(
			pPlayer->GetPos().x,
			GetCollider()->GetPos().y
			- (GetCollider()->GetScale().y + pOtherCollider->GetScale().y) * 0.5f + offset
			- pOtherCollider->GetOffsetPos().y
		);
	}
	break;

	case CollisionDir::Down:
	{

		pPlayer->SetPos(
			pPlayer->GetPos().x,
			GetCollider()->GetPos().y
			+ (GetCollider()->GetScale().y + pOtherCollider->GetScale().y) * 0.5f - offset
			- pOtherCollider->GetOffsetPos().y
		);
	}
	break;

	case CollisionDir::Left:
	{
		pPlayer->SetPos(
			GetCollider()->GetPos().x
			- (GetCollider()->GetScale().x + pOtherCollider->GetScale().x) * 0.5f + offset
			- pOtherCollider->GetOffsetPos().x,
			pPlayer->GetPos().y
		);
	}
	break;

	case CollisionDir::Right:
	{
		pPlayer->SetPos(
			GetCollider()->GetPos().x
			+ (GetCollider()->GetScale().x + pOtherCollider->GetScale().x) * 0.5f - offset
			- pOtherCollider->GetOffsetPos().x,
			pPlayer->GetPos().y
		);
	}
	break;
	}
}

void CPillarDoor::OnCollisionExit(CCollider* pOtherCollider)
{
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

typename CPillarDoor::CollisionDir CPillarDoor::GetCollisionDir(CCollider* pOther)
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