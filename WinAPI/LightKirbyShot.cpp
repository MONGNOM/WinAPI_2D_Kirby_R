#include "framework.h"
#include "LightKirbyShot.h"

#include "CPlayer.h"


LightKirbyShot::LightKirbyShot()
{
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(0, 0);
	m_layer = Layer::LightShot;
	m_strName = L"ºû °ø°Ý";
	m_vecDir = Vector(0, 0);
	m_pIdleImage = nullptr;
}

LightKirbyShot::~LightKirbyShot()
{

}



void LightKirbyShot::Init()
{
	/*m_pIdleImage = RESOURCE->LoadImg(L"PlayerATttack", L"Image\\AT.png");

	m_pIdleImage = RESOURCE->LoadImg(L"PlayerChange", L"Image\\SparkKirby2.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"IdleRight", m_pIdleImage, Vector(0.f, 0.f), Vector(100.f, 99.f), Vector(100.f, 0.f), 10.f, 6);
	m_pAnimator->CreateAnimation(L"IdleLeft", m_pIdleImage, Vector(0.f, 0.f), Vector(100.f, 99.f), Vector(100.f, 0.f), 10.f, 6);


	m_pAnimator->Play(L"IdleRight", false);
	AddComponent(m_pAnimator);*/

	AddCollider(ColliderType::Rect, Vector(50, 50), Vector(0, 0));
}

void LightKirbyShot::Update()
{
	if (BUTTONUP('S'))
	{
		DELETEOBJECT(this);
	}
}

void LightKirbyShot::Render()
{
}

void LightKirbyShot::Release()
{
}

void LightKirbyShot::AnimatorUpdate()
{
	if (m_vecMoveDir.Length() > 0)
		m_vecLookDir = m_vecMoveDir;

	wstring str = L"";

	if (m_bIsMove)	str += L"Move";
	else			str += L"Idle";

	if (m_vecLookDir.x > 0) str += L"Right";
	else if (m_vecLookDir.x < 0) str += L"Left";

	if (m_vecLookDir.y > 0) str += L"Up";
	else if (m_vecLookDir.y < 0) str += L"Down";

	m_pAnimator->Play(str, false);
}

void LightKirbyShot::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}

void LightKirbyShot::OnCollisionEnter(CCollider* pOtherCollider)
{
	
}


void LightKirbyShot::OnCollisionStay(CCollider* pOtherCollider)
{
}

void LightKirbyShot::OnCollisionExit(CCollider* pOtherCollider)
{
}
