#include "CNPC.h"
#include "CGameManager.h"

class CBoss;
class CPillarDoor;

class CBossAppearBlock :
	public CNPC
{
public:
	CBossAppearBlock(CPlayer* player);
	virtual ~CBossAppearBlock();

public:
	CPillarDoor* pDoor;
	CBoss* pBoss;
	float coolTime;
	bool IsStart;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void Talk();
};