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

	m_fJumpTime = 0;
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



	m_pAnimator->Play(L"Gail_Standing_Right", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 5, m_vecScale.y - 8), Vector(0, 4));
	AddGravity(1);
}

void CPlayer::Update()
{

	m_fSpeed = 100;



	if (GetGround() == 0)
	{
		m_behavior = Behavior::Fall;
		if (m_behaviorSave != Behavior::Jump && 
			m_behaviorSave != Behavior::Attack && m_behaviorSave != Behavior::Attack2 && m_behaviorSave != Behavior::Critical && m_behaviorSave != Behavior::CriticalReady)
			m_behaviorSave = m_behavior;
	}
	else
	{
		m_behavior = Behavior::Idle;
		if (m_behaviorSave != Behavior::Attack && m_behaviorSave != Behavior::Attack2 && m_behaviorSave != Behavior::Critical && m_behaviorSave != Behavior::CriticalReady)
			m_behaviorSave = m_behavior;
		
	}

	//공격준비
	if (BUTTONSTAY('X') && !isThingCollision)
	{
		m_behavior = Behavior::AttackReady;
		if (GAME->GetAttackTime() > 2.5)
			m_behavior = Behavior::CriticalReady;
		m_behaviorSave = m_behavior;
	}
	//공격
	if (BUTTONUP('X'))
	{
		if (GAME->GetAttackTime() > 2.5)
			m_behavior = Behavior::Critical;
		else if (GetGround() == 0)
			m_behavior = Behavior::Attack2;
		else
			m_behavior = Behavior::Attack;

		GAME->SetAttackTime(0);
		m_behaviorSave = m_behavior;
	}

	//걷기
	if (BUTTONSTAY(VK_LEFT))
	{
		m_vecMoveDir.x = -1;
		m_behavior = Behavior::Walk;
	}
	else if (BUTTONSTAY(VK_RIGHT))
	{
		m_vecMoveDir.x = 1;
		m_behavior = Behavior::Walk;
	}

	//뛰기
	if (BUTTONSTAY(VK_LEFT) && BUTTONSTAY(VK_SHIFT))
	{
		m_vecMoveDir.x = -1;
		m_behavior = Behavior::Run;
		
	}
	else if (BUTTONSTAY(VK_RIGHT) && BUTTONSTAY(VK_SHIFT))
	{
		m_vecMoveDir.x = 1;
		m_behavior = Behavior::Run;
		
	}

	//앉기
	else if (BUTTONSTAY(VK_DOWN))
	{
		m_behavior = Behavior::Down;
		
	}

	//점프
	if (BUTTONSTAY(VK_DOWN) && BUTTONDOWN('Z') &&GetPlatform()!=0)//하향점프
	{
		m_behavior = Behavior::DownJump;
		m_behaviorSave = Behavior::Fall;
	}
	else if (BUTTONDOWN('Z') && GetGround() !=0)
	{
		m_behavior = Behavior::Jump;
		m_behaviorSave = m_behavior;
	}
	//if (BUTTONSTAY('Z'))
	//{
	//	m_vecPos.y--;
	//	m_fJumpTime += DT;
	//	SetGravity(-m_fJumpTime);
	//}
	

	//데미지
	if (GAME->GetDamage() == true)
	{
		if (GAME->GetDamageTime() < 0.2)
		{
			m_behavior = Behavior::Damage;
			m_behaviorSave = m_behavior;
		}
		else
		{
			GAME->SetDamageTime(0);
			GAME->SetDamage(false);
		}
	}

	if (GAME->GetTalk())
	{
		m_behavior = Behavior::Idle;
		m_behaviorSave = Behavior::Idle;
	}

	BehaviorAction();//행동에 따른 액션

	//모션 불러오기

	if (m_behaviorSave == Behavior::Jump || m_behaviorSave == Behavior::Fall)
	{
		m_behavior = m_behaviorSave;
	}

	if (GAME->GetAttack())
	{
		m_behavior = m_behaviorSave;
	}

	if (m_behaviorSave == Behavior::Damage)
	{
		m_behavior = m_behaviorSave;
	}


	AnimatorUpdate();

	//게임매니저에게 플레이어 정보 전달
	GAME->SetPlayerPos(m_vecPos);
	GAME->SetPlayerDir(m_vecLookDir);




	/*

	

	//데미지
	if (GAME->GetDamage() == true)
	{
		if (GAME->GetDamageTime() < 0.2)
		{
			m_behavior = Behavior::Damage;
			GAME->SetDamageTime(GAME->GetDamageTime() + DT);
			m_vecPos.x += -1 * 200 * DT * m_vecLookDir.x;

			GAME->SetAttackTime(0);
			GAME->SetAttack(false);
		}
		else
		{
			GAME->SetDamageTime(0);
			GAME->SetDamage(false);
		}
	}

	if (!GAME->GetTalk())
	{
		//공격 준비
		if (BUTTONSTAY('X') && !GAME->GetAttack() && !GAME->GetDamage())
		{
			m_behavior = Behavior::AttackReady;
			GAME->SetAttack(true);
		}
		if (GAME->GetAttack() == true)//얼마나 공격준비를 했는지 시간 더하기
			GAME->SetAttackTime(GAME->GetAttackTime() + DT);
		if (GAME->GetAttackTime() > 2.5 && GAME->GetAttack())
			m_behavior = Behavior::CriticalReady;

		//공격
		if (BUTTONUP('X') && GAME->GetAttack())//&& 무기를 가지고 있을 때
		{
			if (GAME->GetAttackTime() > 2.5)//크리티컬 공격
			{
				m_behavior = Behavior::Critical;
				CCritical* pCritical = new CCritical;
				if (m_vecMoveDir.x == -1)
					pCritical->SetPos(m_vecPos.x, m_vecPos.y);
				else if (m_vecMoveDir.x == 1)
					pCritical->SetPos(m_vecPos.x, m_vecPos.y);
				pCritical->SetPos(m_vecPos);
				ADDOBJECT(pCritical);
			}
			else if (GetGround())//일반공격
			{
				m_behavior = Behavior::Attack2;
				CAttack* pAttack = new CAttack();

				if (m_vecMoveDir.x == -1)
					pAttack->SetPos(m_vecPos.x - 10, m_vecPos.y + 7);
				else if (m_vecMoveDir.x == 1)
					pAttack->SetPos(m_vecPos.x + 10, m_vecPos.y + 7);
				pAttack->SetPos(m_vecPos);
				ADDOBJECT(pAttack);
			}
			else//공중공격
			{
				m_behavior = Behavior::Attack;
				CAttack2* pAttack2 = new CAttack2();

				if (m_vecMoveDir.x == -1)
					pAttack2->SetPos(m_vecPos.x - 7, m_vecPos.y + 5);
				else if (m_vecMoveDir.x == 1)
					pAttack2->SetPos(m_vecPos.x + 7, m_vecPos.y + 5);
				pAttack2->SetPos(m_vecPos);
				ADDOBJECT(pAttack2);
			}
			GAME->SetAttackTime(0);
		}


		//떨어지기
		if (!GetGround() && !GAME->GetDamage())
		{
			if (!GAME->GetAttack())
			{
				if (GetGravity() > 100)
					m_behavior = Behavior::Fall;
				else
					m_behavior = Behavior::Jump;
			}
		}
		//앉기
		else if (BUTTONSTAY(VK_DOWN) && GetGround() && !GAME->GetDamage())
		{
			if (!GAME->GetAttack())
			{
				m_behavior = Behavior::Down;
			}
		}
		else
		{
			if (!GAME->GetAttack() && !GAME->GetDamage())
			{
				m_behavior = Behavior::Idle;
			}
		}

		//점프
		if (BUTTONSTAY(VK_DOWN) && BUTTONDOWN('Z') && GetPlatform() != 0 && !GAME->GetDamage())//하향점프
		{
			if (!GAME->GetAttack())
				m_behavior = Behavior::Jump;

			this->SetGround(0);
			this->SetPlatform(0);
			this->SetGravity(1);
		}
		else if (BUTTONDOWN('Z') && GetGround() && !GAME->GetDamage())
		{
			if (!GAME->GetAttack())
				m_behavior = Behavior::Jump;
			m_vecPos.y--;
			SetGravity(-260);
		}



		//걷기
		if (BUTTONSTAY(VK_LEFT) && !GAME->GetDamage())
		{
			if (GetGround() && !GAME->GetAttack())
				m_behavior = Behavior::Walk;
			m_vecMoveDir.x = -1;
		}
		else if (BUTTONSTAY(VK_RIGHT) && !GAME->GetDamage())
		{
			if (GetGround() && !GAME->GetAttack())
				m_behavior = Behavior::Walk;
			m_vecMoveDir.x = +1;
		}

		//뛰기
		if (BUTTONSTAY(VK_LEFT) && BUTTONSTAY(VK_SHIFT) && GetGround() && !GAME->GetDamage())
		{
			if (!GAME->GetAttack())
				m_behavior = Behavior::Run;
			m_vecMoveDir.x = -1;
			m_fSpeed += 100;
		}
		else if (BUTTONSTAY(VK_RIGHT) && BUTTONSTAY(VK_SHIFT) && GetGround() && !GAME->GetDamage())
		{
			if (!GAME->GetAttack())
				m_behavior = Behavior::Run;
			m_vecMoveDir.x = +1;
			m_fSpeed += 100;
		}


		if (BUTTONDOWN(VK_SPACE))
		{
			CreateMissile();
		}
	}
	m_vecPos.x += (m_fSpeed * DT) * m_vecMoveDir.x;


	AnimatorUpdate();

	//게임매니저에게 플레이어 정보 전달
	GAME->SetPlayerPos(m_vecPos);
	GAME->SetPlayerDir(m_vecLookDir);
	
	*/
}

void CPlayer::Render()
{
}

void CPlayer::Release()
{
}

void CPlayer::BehaviorAction()
{
	switch (m_behavior)
	{
	case Behavior::Idle:
		m_vecMoveDir = Vector(0, 0);
		break;
	case Behavior::Walk:
		m_vecPos.x += (m_fSpeed * DT) * m_vecMoveDir.x;
		break;
	case Behavior::Run:
		m_fSpeed += 100;
		m_vecPos.x += (m_fSpeed * DT) * m_vecMoveDir.x;
		break;
	case Behavior::Jump:
	{
		m_vecPos.y--;
		SetGravity(-260);
		break;
	}
	case Behavior::DownJump:
		this->SetGround(0);
		this->SetPlatform(0);
		this->SetGravity(1);
		break;
	case Behavior::Fall:
		break;

	case Behavior::Down:
		break;
	case Behavior::AttackReady:
		GAME->SetAttack(true);
		GAME->SetAttackTime(GAME->GetAttackTime() + DT);
		break;
	case Behavior::Attack:
	{
		CAttack* pAttack = new CAttack();
		if (m_vecMoveDir.x == -1)
			pAttack->SetPos(m_vecPos.x - 10, m_vecPos.y + 7);
		else if (m_vecMoveDir.x == 1)
			pAttack->SetPos(m_vecPos.x + 10, m_vecPos.y + 7);
		pAttack->SetPos(m_vecPos);
		ADDOBJECT(pAttack);
		break;
	}
	case Behavior::Attack2:
	{
		CAttack2* pAttack2 = new CAttack2();

		if (m_vecMoveDir.x == -1)
			pAttack2->SetPos(m_vecPos.x - 7, m_vecPos.y + 5);
		else if (m_vecMoveDir.x == 1)
			pAttack2->SetPos(m_vecPos.x + 7, m_vecPos.y + 5);
		pAttack2->SetPos(m_vecPos);
		ADDOBJECT(pAttack2);
		break;
	}
	case Behavior::Critical:
	{
		CCritical* pCritical = new CCritical;
		if (m_vecMoveDir.x == -1)
			pCritical->SetPos(m_vecPos.x, m_vecPos.y);
		else if (m_vecMoveDir.x == 1)
			pCritical->SetPos(m_vecPos.x, m_vecPos.y);
		pCritical->SetPos(m_vecPos);
		ADDOBJECT(pCritical);
		break;
	}
	case Behavior::CriticalReady:
		break;
	case Behavior::Damage:
		GAME->SetDamageTime(GAME->GetDamageTime() + DT);
		m_vecPos.x += -1 * 200 * DT * m_vecLookDir.x;
		break;
	default:
		break;
	}
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
	if (pOtherCollider->GetObjName() == L"Slug" && !GAME->GetDamage())
	{
		Logger::Debug(L"Slug가 플레이어와 충돌진입");
		m_behavior = Behavior::Damage;
		GAME->SetHp(-5);
		GAME->SetDamage(true);
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
