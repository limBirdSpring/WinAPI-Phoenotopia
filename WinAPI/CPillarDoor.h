#pragma once
#include "CGameObject.h"
#include "framework.h"

class CMarble;
class CStatue;

class CPillarDoor : public CGameObject
{
public:
	enum class CollisionDir { Up, Down, Left, Right, None };
	CPillarDoor();
	virtual ~CPillarDoor();


public :
	CMarble* pMarble = nullptr;
	CStatue* pStatue = nullptr;
	bool isClosed = false;
private:
	float closeY;
	float openY;

	bool isSaveY;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;

	CollisionDir dir;
	float		 offset;
	CollisionDir GetCollisionDir(CCollider* pOther);

};