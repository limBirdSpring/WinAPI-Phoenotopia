#include "framework.h"
#include "CEnding.h"
#include "CImageObject.h"
#include "CImage.h"

CEnding::CEnding()
{
}

CEnding::~CEnding()
{
}

void CEnding::Init()
{
}

void CEnding::Enter()
{
	m_pImage = RESOURCE->LoadImg(L"Dead", L"Image\\Dead.png");
	CImageObject* pDead = new CImageObject;
	pDead->SetImage(m_pImage);
	AddGameObject(pDead);

	CAMERA->ZoomInOut(1);	
	GAME->SetUIRender(false);
	CAMERA->SetMapSize(Vector(m_pImage->GetWidth(), m_pImage->GetHeight()));
	CAMERA->SetTargetPos(Vector(WINSIZEX*0.5 , WINSIZEY*0.5));
}

void CEnding::Update()
{
	switch (talk)
	{
	case 0 :
		m_strDialogue = L"";
		break;
	case 1 :
		m_strDialogue = L"�׷��� ������ ������ ���ư���..";
		break;
	case 2:
		m_strDialogue = L"������ ��� ���� '��û ��κ��̴� ����'�� �Ⱦ� \n���ڰ� �Ǿ";
		break;
	case 3:
		m_strDialogue = L"��������ũ�� �ܶ� ��Ծ��ٰ� �Ѵ�.";
		break;
	case 4:
		m_strDialogue = L"-��-";
		break;
	case 5:
		m_strDialogue = L"�÷������ּż� �����մϴ�.";
		break;
	case 6:
		m_strDialogue = L"<Pheonotopia ����> \n\n������ : WinAPI \n\n���� : �ӻ���\n";
		break;
	case 7:
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Title, 2.f);
		break;
	}

	if (BUTTONDOWN('X'))
		talk++;
}

void CEnding::Render()
{
	RENDER->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	RENDER->Text(m_strDialogue, 0, 0, WINSIZEX, WINSIZEY, Color(255,255,255,1), 40);

}

void CEnding::Exit()
{
}

void CEnding::Release()
{
}
