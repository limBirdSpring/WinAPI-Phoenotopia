#pragma once
#include "CThings.h"
#include "framework.h"


class CItem :
	public CThings
{
public:
	CItem();
	virtual ~CItem();

private:
	Item item;

public :
	void SetItem(Item item) { this->item = item; }
	void SetItem(wstring item) { this->item = GAME->FindItem(item); }

private:
	void Init() override;
	void Update() override;
	void Render() override ;
	void Release() override ;

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override ;
	void OnCollisionExit(CCollider* pOtherCollider) override ;

};