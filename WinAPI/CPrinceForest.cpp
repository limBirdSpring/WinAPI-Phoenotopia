#include "framework.h"
#include "CPrinceForest.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"
#include "CPathManager.h"

#include "CPlayer.h"
#include "CSlug.h"
#include "CCameraController.h"
#include "CButton.h"
#include "CPanel.h"
#include "CResourceManager.h"
#include "CImage.h"
#include "CImageObject.h"
#include "CSoundManager.h"
#include "CGameManager.h"
#include "CDoor.h"
#include "CEventMark.h"
#include "CStatue.h"
#include "CImageEvent.h"
#include "CFrontImage.h"

CPrinceForest::CPrinceForest()
{
	pPlayer = nullptr;
	m_pImage = nullptr;
}

CPrinceForest::~CPrinceForest()
{
}

void CPrinceForest::Init()
{
	pPlayer = new CPlayer();
	AddGameObject(pPlayer);

	pPlayer->SetBehavior(Behavior::Talk);

	m_pImage = RESOURCE->LoadImg(L"Field_Back", L"Image\\Field_Back.png");
	LoadBackground(m_pImage);

	m_pImage = RESOURCE->LoadImg(L"Field_Middle", L"Image\\Field_Middle.png");
	LoadMiddleground(m_pImage);

	m_pImage = RESOURCE->LoadImg(L"Cloud", L"Image\\Cloud.png");



}

void CPrinceForest::Enter()
{
	GAME->SetUIRender(true);
	CAMERA->FadeIn(0.25f);

	//pLoad_BGM = RESOURCE->FindSound(L"Panselo");
	//SOUND->Play(pLoad_BGM, 1, true);


	CAMERA->SetMapSize(Vector(m_pImage->GetWidth(), m_pImage->GetHeight()));
	CAMERA->ZoomInOut(3);
	CAMERA->SetTargetPos(Vector(m_pImage->GetWidth() * 0.5, m_pImage->GetHeight()));

	pPlayer->SetPos(GAME->GetPlayerStartPos());
	pPlayer->SetDir(GAME->GetPlayerStartDir());
	pPlayer->SetGravity(1);
	pPlayer->SetPlatform(0);
	pPlayer->SetGround(0);

	CAMERA->FadeIn(0.25f);
	LoadTile(GETPATH + L"Tile\\PrinceForest.tile");
}

void CPrinceForest::Update()
{
}

void CPrinceForest::Render()
{

}

void CPrinceForest::Exit()
{
}

void CPrinceForest::Release()
{
}
