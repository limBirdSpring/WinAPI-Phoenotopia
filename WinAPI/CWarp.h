#pragma once
#include "CThings.h"
#include "framework.h"
#include "CAnimator.h"

class CImage;
class CScene;

class CWarp :
	public CThings
{
public:
	CWarp();
	virtual ~CWarp();

private:


	Vector m_vecPlayerStartPos; //씬으로 갔을 경우 플레이어 위치
	GroupScene m_pScene; //문을 통해 갈 수 있는 씬

public:
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