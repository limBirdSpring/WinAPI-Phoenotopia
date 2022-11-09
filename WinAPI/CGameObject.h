#pragma once
#include "WinAPI.h"

class CEventManager;
class CCollisionManager;
class CScene;
class CComponent;
class CCollider;
class CGravity;
class CLineMove;
enum class ColliderType;
class CImage;
class CAnimator;

// ���ӿ�����Ʈ : 
// �� ���� �����ϴ� ��ü, ex) ĳ����, �̻���, ����, ������, ��
// ���ӿ�����Ʈ�� ĸ��ȭ�Ͽ� �ൿ�� ǥ���� ������ ���
// �ٸ� ���ӿ�����Ʈ�� ���������� ������ �� ����
class CGameObject
{
	friend CEventManager;
	friend CCollisionManager;
	friend CScene;
	friend CCollider;
public:
	CGameObject();
	virtual ~CGameObject();

protected:
	Vector m_vecPos;	// ���ӿ�����Ʈ�� ��ġ
	Vector m_vecScale;	// ���ӿ�����Ʈ�� ũ��
	Layer m_layer;		// ���ӿ�����Ʈ�� ���̾�
	wstring m_strName;	// ���ӿ�����Ʈ�� �̸�
	Vector m_vecMoveDir; //���ӿ�����Ʈ�� ����

	CImage* m_pImage;
	CAnimator* m_pAnimator;

	float m_fSpeed;

public :
	Vector GetPos();
	void SetPos(Vector pos);
	void SetPos(float x, float y);
	Vector GetScale();
	void SetScale(Vector scale);
	void SetScale(float x, float y);
	Layer GetLayer();
	void SetLayer(Layer layer);
	wstring GetName();
	void SetName(wstring name);
	Vector GetDir() { return m_vecMoveDir; }
	void SetDir(Vector dir) { m_vecMoveDir = dir; }

	void SetGravity(float velocity);
	float GetGravity();


private:
	bool m_bReservedDelete;		// ���ӿ�����Ʈ�� ������������ ����
	bool m_bSafeToDelete;		// ���ӿ�����Ʈ�� �����ص� ���������� ����

	void SetReserveDelete();	// ���ӿ�����Ʈ ���� ����
	bool GetSafeToDelete();		// ���ӿ�����Ʈ ���� ���� ���� Ȯ��
	void SetSafeToDelete();		// ���ӿ�����Ʈ ���� ���� ���� ǥ��
public:
	bool GetReserveDelete();		// ���ӿ�����Ʈ�� ������������ Ȯ��

protected:
	list<CComponent*> m_listComponent;	// ������Ʈ���� ������ �ڷᱸ��

	void AddComponent(CComponent* component);		// ������Ʈ �߰�
	void RemoveComponent(CComponent* component);	// ������Ʈ ����

	void ComponentRender();

	// �浹 ������Ʈ
private:
	CCollider* m_pCollider;
	CGravity* m_pGravity;
	CLineMove* m_pLineMove;

protected:
	CCollider* GetCollider();
	void AddCollider(ColliderType type, Vector scale, Vector offsetPos);
	void RemoveCollider();

	virtual void OnCollisionEnter(CCollider* pOtherCollider) {};	// �浹üũ�� Ȯ���ϴ� ������Ʈ�� �������Ͽ� ���
	virtual void OnCollisionStay(CCollider* pOtherCollider) {};	// �浹üũ�� Ȯ���ϴ� ������Ʈ�� �������Ͽ� ���
	virtual void OnCollisionExit(CCollider* pOtherCollider) {};	// �浹üũ�� Ȯ���ϴ� ������Ʈ�� �������Ͽ� ���

	void AddGravity(float velocity);
	void AddLineMove(Vector start, Vector end, float speed = 50);


public:
	void SetGround(int ground);
	int GetGround();
	void SetPlatform(int platform);
	int GetPlatform();



protected:
	// ���ӿ�����Ʈ �θ� ���� �Լ��� :
	// ���ӿ�����Ʈ�� �ִ� ��� ������Ʈ���� ����
	virtual void GameObjectInit();
	virtual void GameObjectUpdate();
	virtual void GameObjectPhysicsUpdate();
	virtual void GameObjectRender();
	virtual void GameObjectRelease();

	// ���������Լ�:
	// �Լ��� �߻�ȭ�Ͽ� ��üȭ���� ���� ��� �ν��Ͻ� ������ ����
	// ���ӿ�����Ʈ�� ��ӹ޾� ���������Լ����� ��üȭ���� ���ӿ�����Ʈ�� �ϼ���Ŵ
	virtual void Init() = 0;		// �ʱ�ȭ
	virtual void Update() = 0;		// ���ӿ�����Ʈ�� �ൿ����
	virtual void Render() = 0;		// ���ӿ�����Ʈ�� ǥ������
	virtual void Release() = 0;		// ������
};
