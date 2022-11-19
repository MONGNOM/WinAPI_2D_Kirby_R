#include "framework.h"
#include "CGround.h"

CGround::CGround()
{
	m_pImage = nullptr;
	m_layer = Layer::Ground;
}

CGround::~CGround()
{
}

CImage* CGround::GetIamge()
{
	return m_pImage;
}

void CGround::SetImage(CImage* pImage)
{
	m_pImage = pImage;

}


void CGround::Init()
{
}

void CGround::Update()
{
}

void CGround::Render()
{

	RENDER->Image(
		m_pImage,
		0,0, 5058,1728

	);
}

void CGround::Release()
{
}
