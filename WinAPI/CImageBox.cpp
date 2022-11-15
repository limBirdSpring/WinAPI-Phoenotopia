#include "framework.h"
#include "CImageBox.h"
#include "CImage.h"

CImageBox::CImageBox()
{
	m_layer = Layer::TalkBox;
}

CImageBox::~CImageBox()
{
}

void CImageBox::Init()
{
}

void CImageBox::Update()
{

	
}

void CImageBox::Render()
{
	Vector pos = CAMERA->ScreenToWorldPoint(Vector(WINSIZEX * 0.5, WINSIZEY * 0.5), false);


	RENDER->Image(pEventImage, pos.x - pEventImage->GetWidth() * 0.5 / 2, pos.y - pEventImage->GetHeight() * 0.5 / 2, pos.x + pEventImage->GetWidth() * 0.5 / 2, pos.y + pEventImage->GetHeight() * 0.5 / 2);

}

void CImageBox::Release()
{
}
