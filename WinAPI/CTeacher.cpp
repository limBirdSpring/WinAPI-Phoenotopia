#include "framework.h"
#include "CTeacher.h"

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
#include "CCameraManager.h"
#include "CPlayer.h"
#include "CTalkBox.h"


CTeacher::CTeacher(CPlayer* player)
{
	pPlayer = player;
	m_vecScale = Vector(18, 32);
	m_strDialogue = L"";
	talk = 0;
}

CTeacher::~CTeacher()
{
}

void CTeacher::Init()
{

	m_pImage = RESOURCE->LoadImg(L"Teacher_Idle", L"Image\\Teacher_Idle.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"Teacher_Idle_Right", m_pImage, Vector(0, 0), Vector(100, 100), Vector(150, 0), 0.5, 4);
	m_pAnimator->CreateAnimation(L"Teacher_Idle_Left", m_pImage, Vector(0, 150), Vector(100, 100), Vector(150, 0), 0.5, 4);

	m_pAnimator->Play(L"Teacher_Idle_Left");
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(m_vecScale.x - 0.1, m_vecScale.y - 0.1), Vector(0, 4));
}

void CTeacher::Update()
{
	if (changeTalkTopic == 1 && GAME->isItemSetting(L"방망이"))
	{
		changeTalkTopic++;
	}

	if (talk > 0)
	{
		if (BUTTONDOWN('X'))
		{
			talk++;
			Talk();
		}
	}

	if (m_choose != 0)
	{
		if (BUTTONDOWN(VK_UP))
		{
			m_choosing--;
		}
		if (BUTTONDOWN(VK_DOWN))
		{
			m_choosing++;
		}
		if (m_choosing <= 0)
			m_choosing = 1;
		else if (m_choosing > m_choose)
			m_choosing = m_choose;
	}
}

void CTeacher::Render()
{
	if (talk > 0)
	{
		pTalkBox->m_choose = &this->m_choose;
		pTalkBox->m_choosing = &this->m_choosing;
		pTalkBox->m_strDialogue = this->m_strDialogue;

	}
	
}

void CTeacher::Release()
{
}

void CTeacher::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		if (BUTTONDOWN('X'))
		{
			CAMERA->ZoomInOut(2.5, 1);

			talk++;
			GAME->SetTalk(true);
			Talk();
			pPlayer->m_vecPos.x = this->m_vecPos.x - 30;
			pPlayer->m_vecMoveDir.x = 1;
			pPlayer->m_behavior = Behavior::Talk;
			
			pTalkBox = new CTalkBox;
			pTalkBox->SetPos(this->GetPos());
			ADDOBJECT(pTalkBox);
		}
	}
}

void CTeacher::Talk()
{
	if (changeTalkTopic == 0)
	{
		switch (talk)
		{
		case 0:
			m_strDialogue = L"";
			break;
		case 1:
			m_strDialogue = L"오. 게일왔구나. 얼굴 보기가 참 힘들구나.";
			break;
		case 2:
			m_strDialogue = L"수련은 잘 하고 있냐? 아니, 그럴리가 없지. 이렇게 학원에 안나오는데.";
			break;
		case 3:
			m_strDialogue = L"뭐? 무기를 받으러 왔다고? 벌써 잃어버린거냐?";
			break;
		case 4:
			m_strDialogue = L"허, 나참. 그래. 다시 줄테니 대신 이제 열심히 수련해야한다. 게을리해서는 안돼.";
			break;
		case 5:
			m_strDialogue = L"자. 여기 받거라.";
			GAME->PushBackInvenItem(L"방망이");
			break;
		case 6:
			m_strDialogue = L"아 참. 무기를 장착하는 방법을 잊은 건 아니겠지?";
			break;
		case 7:
			m_strDialogue = L"I를 눌러 인벤토리에 들어가 무기를 선택한 후 X를 누르면 장착 버튼이 나온단다.";
			break;
		case 8:
			m_strDialogue = L"자. 한번 해보렴.";
			break;
		default:
			CAMERA->ZoomInOut(2, 1);
			m_strDialogue = L"";
			GAME->SetTalk(false);
			talk = 0;
			changeTalkTopic++;
			DELETEOBJECT(pTalkBox);
			break;
		}
	}
	else if (changeTalkTopic == 1)
	{
		switch (talk)
		{
		case 0:
			m_strDialogue = L"";
			break;
		case 1:
			m_strDialogue = L"I를 눌러 인벤토리에 들어가 무기를 선택한 후 X를 누르면 장착 버튼이 나온단다.";
			break;
		case 2:
			m_strDialogue = L"자. 한번 해보렴.";
			break;
		default:
			CAMERA->ZoomInOut(2, 1);
			m_strDialogue = L"";
			GAME->SetTalk(false);
			talk = 0;
			DELETEOBJECT(pTalkBox);
			break;
		}
	}
	else if (changeTalkTopic == 2)
	{
		switch (talk)
		{
		case 0:
			m_strDialogue = L"";
			break;
		case 1:
			m_strDialogue = L"뭐? 설마 기본적인 공격 동작도 잊어먹은건 아니겠지?";
			break;
		case 2:
			m_strDialogue = L"어휴. 그래 알았다. 2주 안나왔으면 그럴만 하지.";
			break;
		case 3:
			m_strDialogue = L"처음부터 알려줄테니 잘 듣거라.";
			break;
		case 4:
			m_strDialogue = L"무기를 장착한 상태에서 X키를 누르면 무기를 휘두를 수 있단다.";
			break;
		case 5:
			m_strDialogue = L"점프를 하며 X키를 누르면 일반공격보다 위력이 센 공중공격을 할 수 있지.";
			break;
		case 6:
			m_strDialogue = L"자. 옆에 수련용 슬러그가 있으니, 한번 연습해보렴.";
			break;
		case 7:
			m_strDialogue = L"슬러그는 위험한 몬스터 아니냐고?";
			break;
		case 8:
			m_strDialogue = L"그래. 하지만 저 슬러그는 연습용으로 길들여져서 아무런 데미지를 입히지 못한단다.";
			break;
		case 9:
			m_strDialogue = L"하지만 야생 슬러그는 공격을 해도 데미지가 먹지 않는 무시무시한 몬스터이니 가급적 공격을 하지 않는게 좋단다.";
			break;
		case 10:
			m_strDialogue = L"충분히 연습을 했다면 나에게 다시 말을 걸거라.";
			break;
		case 11:
			m_strDialogue = L"그럼 다음 기술인 크리티컬 공격에 대해 설명해주지.";
			break;
		default:
			CAMERA->ZoomInOut(2, 1);
			m_strDialogue = L"";
			GAME->SetTalk(false);
			talk = 0;
			changeTalkTopic++;
			DELETEOBJECT(pTalkBox);
			break;
		}
	}
	else if (changeTalkTopic == 3)
	{
		switch (talk)
		{
		case 0:
			m_strDialogue = L"";
			break;
		case 1:
			m_strDialogue = L"충분히 연습은 했겠지?";
			break;
		case 2:
			m_strDialogue = L"다음은 크리티컬 공격이다. 크리티컬 공격은 제일 위력이 세지.";
			break;
		case 3:
			m_strDialogue = L"X키를 일정시간동안 누르고 있으면 무기에 차징에너지가 채워진단다.";
			break;
		case 4:
			m_strDialogue = L"그 상태에서 X키를 떼면 크리티컬 공격이 발동되지.";
			break;
		case 5:
			m_strDialogue = L"크리티컬 공격은 위력이 세지만, 공격준비 시간동안에는 이동속도가 느려지니 조심해서 써야한단다.";
			break;
		case 6:
			m_strDialogue = L"자. 이번에도 한번 연습해보거라.";
			break;
		default:
			CAMERA->ZoomInOut(2, 1);
			m_strDialogue = L"";
			GAME->SetTalk(false);
			talk = 0;
			changeTalkTopic++;
			DELETEOBJECT(pTalkBox);
			break;
		}
	}
	else if (changeTalkTopic == 4)
	{
		switch (talk)
		{
		case 0:
			m_strDialogue = L"";
			break;
		case 1:
			m_strDialogue = L"그래. 이정도면 충분히 연습이 되었겠지.";
			break;
		case 2:
			m_strDialogue = L"앞으로도 학원에 열심히 나와서 수련을 하도록 하렴.";
			break;
		default:
			CAMERA->ZoomInOut(2, 1);
			m_strDialogue = L"";
			GAME->SetTalk(false);
			talk = 0;
			changeTalkTopic++;
			DELETEOBJECT(pTalkBox);
			break;
		}
	}
	else
	{
	switch (talk)
	{
	case 0:
		m_strDialogue = L"";
		break;
	case 1:
		m_strDialogue = L"무슨일이냐 게일?";
		break;
	case 2:
		m_strDialogue = L"너 설마 수련하러 온거냐? 오늘은 해가 서쪽에서 뜨겠구만.";
		break;
	case 3:
		m_strDialogue = L"\n\n 공격에 대해 다시 듣고싶어요.\n 안녕히계세요.";
		m_choose = 2;
		break;
	case 4:
		if (m_choosing == 1)
		{
			m_strDialogue = L"또 까먹은거냐? 알겠다. 나에게 다시 말을 걸거라.";
			changeTalkTopic = 2;
		}
		else
		{
			m_strDialogue = L"그래. 잘가렴.";
		}
		m_choose = 0;
		m_choosing = 1;
		break;
	default:
		CAMERA->ZoomInOut(2, 1);
		m_strDialogue = L"";
		GAME->SetTalk(false);
		talk = 0;
		DELETEOBJECT(pTalkBox);
		break;
	}
	}
}
