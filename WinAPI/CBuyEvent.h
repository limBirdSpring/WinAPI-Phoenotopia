
#include "CNPC.h"
#include "CGameManager.h"

class CBuyEvent :
	public CNPC
{
public:
	CBuyEvent();
	virtual ~CBuyEvent();

public:
	Item item; //�������� ������ �Է��ؼ� ����ؾ���.

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;
	void Talk();
};