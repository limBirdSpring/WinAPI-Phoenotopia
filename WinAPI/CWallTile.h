#pragma once
#pragma once
#include "CTile.h"
class CWallTile :
	public CTile
{
public:
	enum class CollisionDir { Up, Down, Left, Right, None };
	CWallTile();
	virtual ~CWallTile();

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;


private:
	void OnCollisionEnter(CCollider* pOther) override;
	void OnCollisionStay(CCollider* pOther) override;
	void OnCollisionExit(CCollider* pOther) override;

	CollisionDir dir;
	float		 offset;
	CollisionDir GetCollisionDir(CCollider* pOther);
};

