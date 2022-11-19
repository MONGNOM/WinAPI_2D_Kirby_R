#include "framework.h"
#include "CCameraController.h"

#include "CInputManager.h"
#include "CCameraManager.h"

CCameraController::CCameraController()
{
}

CCameraController::~CCameraController()
{
}

void CCameraController::Init()
{
}

void CCameraController::Update()
{
	Vector dir;
	if (m_vecPos.x >= 5058 && m_vecPos.x <= 0 )
		dir.x = 0;
	else if (m_vecPos.y >= -300 && m_vecPos.y <= 800)
		dir.y = 0;

	/*if (LMOUSEDOWN(false))
	{
		CAMERA->SetTargetPos(MOUSEWORLDPOS, 1);
	}

	Vector dir;
	if (BUTTONSTAY('A'))
	{
		dir.x = -3;
	}
	else if (BUTTONSTAY('D'))
		dir.x = 3;
	else dir.x = 0;

	if (BUTTONSTAY('W'))
		dir.y = -3;
	else if (BUTTONSTAY('S'))
		dir.y = 3;
	else
		dir.y = 0;
		
	CAMERA->Scroll(dir, m_fScrollSpeed);
	*/
}

void CCameraController::Render()
{
}

void CCameraController::Release()
{
}
