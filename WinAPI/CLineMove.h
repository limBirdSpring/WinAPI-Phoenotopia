#pragma once
#include "CComponent.h"

class CGameObject;

class CLineMove : public CComponent
{
	friend CGameObject;

public:
	CLineMove();
	virtual ~CLineMove();

private:
	Vector m_vecStart;
	Vector m_vecEnd;
	float m_fSpeed;

	bool repeat;

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

protected :
	Vector GetStart() { return m_vecStart; }
	Vector GetEnd() { return m_vecEnd; }
	float GetSpeed() { return m_fSpeed; }

	void SetStart(Vector start) { m_vecStart = start; }
	void SetEnd(Vector end) { m_vecEnd = end; }
	void SetSpeed(float speed) { m_fSpeed = speed; }

};