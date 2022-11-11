#include "framework.h"
#include "CPlayer.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CResourceManager.h"
#include "CGameManager.h"
#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"

#include "CMissile.h"
#include "CAttack.h"
#include "CAttack2.h"
#include "CCritical.h"

#include "CStateIdle.h"
#include "CStateWalk.h"
#include "CStateDown.h"
#include "CStateRun.h"
#include "CStateJump.h"
#include "CStateDownJump.h"
#include "CStateAttack.h"
#include "CStateAttack2.h"
#include "CStateAttackReady.h"
#include "CStateCritical.h"
#include "CStateDamage.h"
#include "CStateCriticalReady.h"
#include "CStateFall.h"
#include "CStateTalk.h"

CPlayer::CPlayer()
{
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(18, 32);
	m_layer = Layer::Player;
	m_strName = L"플레이어";
	m_fSpeed = 100;

	m_pIdleImage = nullptr;
	m_pMoveImage = nullptr;
	m_pRunImage = nullptr;
	m_pJumpImage = nullptr;
	m_pDownImage = nullptr;
	m_pAttackImage  = nullptr;
	m_pAttack2Image = nullptr;
	m_pCriticalImage = nullptr;
	m_pAttackReadyImage = nullptr;
	m_pDamageImage = nullptr;

	isThingCollision = false;



	m_vecMoveDir = Vector(0, 0);
	m_vecLookDir = Vector(0, -1);
	m_behavior = Behavior::Idle;
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
#pragma region 이미지
	m_pIdleImage = RESOURCE->LoadImg(L"Gail_Standing", L"Image\\Gail_Standing.png");
	m_pMoveImage = RESOURCE->LoadImg(L"Gail_Walking", L"Image\\Gail_Walking.png");
	m_pRunImage = RESOURCE->LoadImg(L"Gail_Run", L"Image\\Gail_Run.png");
	m_pJumpImage = RESOURCE->LoadImg(L"Gail_Jump", L"Image\\Gail_Jump.png");
	m_pDownImage = RESOURCE->LoadImg(L"Gail_Down", L"Image\\Gail_Down.png");

	m_pAttackImage = RESOURCE->LoadImg(L"Gail_Attack", L"Image\\Gail_Attack.png");
	m_pAttack2Image = RESOURCE->LoadImg(L"Gail_Attack2", L"Image\\Gail_Attack2.png");
	m_pCriticalImage = RESOURCE->LoadImg(L"Gail_Critical", L"Image\\Gail_Critical.png");
	m_pAttackReadyImage = RESOURCE->LoadImg(L"Gail_AttackReady", L"Image\\Gail_AttackReady.png");
	m_pDamageImage = RESOURCE->LoadImg(L"Gail_Damage", L"Image\\Gail_Damage.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"Gail_Standing_Right", m_pIdleImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.2f, 6);
	m_pAnimator->CreateAnimation(L"Gail_Standing_Left", m_pIdleImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.2f, 6);
	m_pAnimator->CreateAnimation(L"Gail_Walking_Right", m_pMoveImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.1f, 8);
	m_pAnimator->CreateAnimation(L"Gail_Walking_Left", m_pMoveImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.1f, 8);
	m_pAnimator->CreateAnimation(L"Gail_Run_Right", m_pRunImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.1f, 6);
	m_pAnimator->CreateAnimation(L"Gail_Run_Left", m_pRunImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.1f, 6);
	m_pAnimator->CreateAnimation(L"Gail_Jump_Right", m_pJumpImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.1f, 13, false);
	m_pAnimator->CreateAnimation(L"Gail_Jump_Left", m_pJumpImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.1f, 13, false);
	m_pAnimator->CreateAnimation(L"Gail_Fall_Right", m_pJumpImage, Vector(750, 0), Vector(100, 100), Vector(150, 0), 0.1f, 8);
	m_pAnimator->CreateAnimation(L"Gail_Fall_Left", m_pJumpImage, Vector(750, 150), Vector(100, 100), Vector(150, 0), 0.1f, 8);
	m_pAnimator->CreateAnimation(L"Gail_Down_Right", m_pDownImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.15f, 4, false);
	m_pAnimator->CreateAnimation(L"Gail_Down_Left", m_pDownImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.15f, 4, false);

	m_pAnimator->CreateAnimation(L"Gail_Attack2_Right", m_pAttackImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.08f, 7, false);
	m_pAnimator->CreateAnimation(L"Gail_Attack2_Left", m_pAttackImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.08f, 7, false);
	m_pAnimator->CreateAnimation(L"Gail_Attack_Right", m_pAttack2Image, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.08f, 5, false);
	m_pAnimator->CreateAnimation(L"Gail_Attack_Left", m_pAttack2Image, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.08f, 5, false);
	m_pAnimator->CreateAnimation(L"Gail_AttackReady_Right", m_pAttackReadyImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.1f, 12);
	m_pAnimator->CreateAnimation(L"Gail_AttackReady_Left", m_pAttackReadyImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.1f, 12);
	m_pAnimator->CreateAnimation(L"Gail_Critical_Right", m_pCriticalImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.1f, 10, false);
	m_pAnimator->CreateAnimation(L"Gail_Critical_Left", m_pCriticalImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.1f, 10, false);
	m_pAnimator->CreateAnimation(L"Gail_CriticalReady_Right", m_pAttackReadyImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.1f, 3);
	m_pAnimator->CreateAnimation(L"Gail_CriticalReady_Left", m_pAttackReadyImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.1f, 3);
	m_pAnimator->CreateAnimation(L"Gail_Damage_Right", m_pDamageImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.05f, 4, false);
	m_pAnimator->CreateAnimation(L"Gail_Damage_Left", m_pDamageImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.05f, 4, false);

#pragma endregion 이미지

	m_pAnimator->Play(L"Gail_Standing_Right", false);
	AddComponent(m_pAnimator);

	m_mapPlayerState.insert(make_pair(Behavior::Idle, new CStateIdle(this)));
	m_mapPlayerState.insert(make_pair(Behavior::Walk, new CStateWalk(this)));
	m_mapPlayerState.insert(make_pair(Behavior::Run, new CStateRun(this)));
	m_mapPlayerState.insert(make_pair(Behavior::Jump, new CStateJump(this)));
	m_mapPlayerState.insert(make_pair(Behavior::Down, new CStateDown(this)));
	m_mapPlayerState.insert(make_pair(Behavior::DownJump, new CStateDownJump(this)));
	m_mapPlayerState.insert(make_pair(Behavior::Attack, new CStateAttack(this)));
	m_mapPlayerState.insert(make_pair(Behavior::Attack2, new CStateAttack2(this)));
	m_mapPlayerState.insert(make_pair(Behavior::AttackReady, new CStateAttackReady(this)));
	m_mapPlayerState.insert(make_pair(Behavior::Critical, new CStateCritical(this)));
	m_mapPlayerState.insert(make_pair(Behavior::CriticalReady, new CStateCriticalReady(this)));
	m_mapPlayerState.insert(make_pair(Behavior::Damage, new CStateDamage(this)));
	m_mapPlayerState.insert(make_pair(Behavior::Fall, new CStateFall(this)));
	m_mapPlayerState.insert(make_pair(Behavior::Talk, new CStateTalk(this)));


	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 5, m_vecScale.y - 8), Vector(0, 4));
	AddGravity(1);
}

void CPlayer::Update()
{

	m_mapPlayerState.find(m_behavior)->second->Update();

	AnimatorUpdate();

	//게임매니저에게 플레이어 정보 전달
	GAME->SetPlayerPos(m_vecPos);
	GAME->SetPlayerDir(m_vecLookDir);

}

void CPlayer::Render()
{
}

void CPlayer::Release()
{
}



void CPlayer::AnimatorUpdate()
{
	if (m_vecMoveDir.Length() > 0)
		m_vecLookDir = m_vecMoveDir;

	wstring str = L"Gail";

	switch (m_behavior)
	{
	case Behavior::Walk: str += L"_Walking";
		break;
	case Behavior::Run: str += L"_Run";
		break;
	case Behavior::Jump: str += L"_Jump";
		break;
	case Behavior::Fall: str += L"_Fall";
		break;
	case Behavior::Down: str += L"_Down";
		break;
	case Behavior::Attack: str += L"_Attack";
		break;
	case Behavior::Attack2: str += L"_Attack2";
		break;
	case Behavior::Critical: str += L"_Critical";
		break;
	case Behavior::AttackReady: str += L"_AttackReady";
		break;
	case Behavior::CriticalReady: str += L"_CriticalReady";
		break;
	case Behavior::Damage: str += L"_Damage";
		break;
	default: str += L"_Standing";
	}

	if (m_vecLookDir.x > 0) str += L"_Right";
	else if (m_vecLookDir.x <= 0) str += L"_Left";

	m_pAnimator->Play(str, false);
}

void CPlayer::CreateMissile()
{
	Logger::Debug(L"미사일 생성");

	CMissile* pMissile = new CMissile();
	pMissile->SetPos(m_vecPos);
	pMissile->SetDir(Vector(1, 0));
	ADDOBJECT(pMissile);

}

void CPlayer::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"Slug" && m_behavior != Behavior::Damage)
	{
		Logger::Debug(L"Slug가 플레이어와 충돌진입");
		m_behavior = Behavior::Damage;
		GAME->SetHp(-5);
	}

	if (pOtherCollider->GetObjName() == L"벽")
	{
		m_vecMoveDir.x = 0;
	}

	if (pOtherCollider->GetOwner()->GetLayer() == Layer::Things || pOtherCollider->GetOwner()->GetLayer() == Layer::NPC)
	{
		isThingCollision = true;
	}
}

void CPlayer::OnCollisionStay(CCollider* pOtherCollider)
{
	
}

void CPlayer::OnCollisionExit(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetOwner()->GetLayer() == Layer::Things || pOtherCollider->GetOwner()->GetLayer() == Layer::NPC)
	{
		isThingCollision = false;
	}
}
