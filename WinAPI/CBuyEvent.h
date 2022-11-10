
#include "CNPC.h"
#include "CGameManager.h"

class CBuyEvent :
	public CNPC
{
public:
	CBuyEvent();
	virtual ~CBuyEvent();

public:
	Item item; //아이템을 무조건 입력해서 사용해야함.

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;
	void Talk();
};