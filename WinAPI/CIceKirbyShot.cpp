#include "framework.h"
#include "CIceKirbyShot.h"

CIceKirbyShot::CIceKirbyShot()
{
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(0, 0);
	m_layer = Layer::LightShot;
	m_strName = L"ºû °ø°Ý";
	m_vecDir = Vector(0, 0);
	m_pIdleImage = nullptr;
}

CIceKirbyShot::~CIceKirbyShot()
{
}

void CIceKirbyShot::AnimatorUpdate()
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

void CIceKirbyShot::Init()
{
	
	m_pIdleImage = RESOURCE->LoadImg(L"IcePlayerATttackEffect", L"Image\\Kirby\\Ice\\IceKirbyAttackEffect.png");


	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"IdleRight", m_pIdleImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 7);
	m_pAnimator->CreateAnimation(L"IdleLeft", m_pIdleImage, Vector(400.f, 100.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.05f, 7);


	m_pAnimator->Play(L"IdleRight", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(50, 50), Vector(0, 0));
}

void CIceKirbyShot::Update()
{
	if (BUTTONUP('S'))
	{
		DELETEOBJECT(this);
	}
}

void CIceKirbyShot::Render()
{
}

void CIceKirbyShot::Release()
{
}

void CIceKirbyShot::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}

void CIceKirbyShot::OnCollisionEnter(CCollider* pOtherCollider)
{
}

void CIceKirbyShot::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CIceKirbyShot::OnCollisionExit(CCollider* pOtherCollider)
{
}
