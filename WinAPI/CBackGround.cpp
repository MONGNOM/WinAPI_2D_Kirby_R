#include "framework.h"
#include "CBackGround.h"

#include "CRenderManager.h"

#include "CImage.h"



CBackGround::CBackGround()
{
	m_pImage = nullptr;
	m_layer = Layer::BackGround;
	
}

CBackGround::~CBackGround()
{
}

CImage* CBackGround::GetIamge()
{
	return m_pImage;
}

void CBackGround::SetImage(CImage* pImage)
{
	m_pImage = pImage;
}

void CBackGround::Init()
{
}

void CBackGround::Update()
{
	if (BUTTONSTAY(VK_LEFT))
	{
		m_vecPos.x -= 10;
	}
	else;

}

void CBackGround::Render()
{


	
	if (nullptr != m_pImage)
	{
		RENDER->Image(
			m_pImage,
			0,-500,5058,800
	
		);
	}
}

void CBackGround::Release()
{
}
