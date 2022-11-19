#include "framework.h"
#include "CDoor.h"


#include "CCollider.h"


CDoor::CDoor()
{
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(50, 50);
	m_layer = Layer::Door;
	m_strName = L"��";
	DoorOpen = false;
}

CDoor::~CDoor()
{
}

void CDoor::Init()
{
	AddCollider(ColliderType::Rect, Vector(70, 70), Vector(0, 0));
}

void CDoor::Update()
{
	if (BUTTONDOWN(VK_UP) && DoorOpen == true)
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Boss, 0.25f);
	}

	
}

void CDoor::Render()
{
	RENDER->FrameCircle(
		m_vecPos.x,
		m_vecPos.y,
		m_vecScale.x);
}

void CDoor::Release()
{
}

void CDoor::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"�÷��̾�")
	{
		DoorOpen = true;
	}
}

void CDoor::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"�÷��̾�")
	{
		DoorOpen = true;
	}
}

void CDoor::OnCollisionExit(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"�÷��̾�")
	{
		DoorOpen = false;
	}
}
