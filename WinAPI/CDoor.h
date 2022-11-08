#pragma once
#include "CThings.h"
#include "framework.h"
#include "CAnimator.h"

class CImage;
class CScene;

class CDoor :
	public CThings
{
public:
	CDoor();
	virtual ~CDoor();

private:

	
	bool haveImage = true;
	bool isOpen;

	Vector m_vecPlayerStartPos; //������ ���� ��� �÷��̾� ��ġ
	GroupScene m_pScene; //���� ���� �� �� �ִ� ��

public :
	void SetImage(bool img) { haveImage = img; }
	void SetScene(GroupScene scene) { m_pScene = scene; }
	void SetPlayerStartPos(Vector pos) { m_vecPlayerStartPos = pos; }

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;

	void AnimatorUpdate();
};