#pragma once
#include "CGameObject.h"
#include "framework.h"
#include "CAnimator.h"

class CImage;
class CScene;

class CDoor :
	public CGameObject
{
public:
	CDoor();
	virtual ~CDoor();

private:

	
	bool haveImage = true;
	bool isOpen;

	Vector m_vecPlayerStartPos; //������ ���� ��� �÷��̾� ��ġ
	Vector m_vecPlayerStartDir; //������ ���� ��� �÷��̾� ����
	GroupScene m_pScene; //���� ���� �� �� �ִ� ��

public :
	void SetImage(bool img) { haveImage = img; }
	void SetScene(GroupScene scene) { m_pScene = scene; }
	void SetPlayerStartPos(Vector pos) { m_vecPlayerStartPos = pos; }
	void SetPlayerStartDir(Vector dir) { m_vecPlayerStartDir = dir; }

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