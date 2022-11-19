#include "framework.h"
#include "KirbyEat.h"

#include "CPlayer.h"

KirbyEat::KirbyEat()
{

	m_vecPos = Vector( 0, 0);
	m_vecScale = Vector(0, 0);
	m_layer = Layer::Eat;
	m_strName = L"먹기";
	m_vecDir = Vector(0, 0);
	m_pIdleImage = nullptr;

}

KirbyEat::~KirbyEat()
{
}

void KirbyEat::Init()
{
	
	m_pIdleImage = RESOURCE->LoadImg(L"PlayerATttack", L"Image\\Kirby\\Basic\\KirbyEat.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"IdleRight", m_pIdleImage, Vector(0.f, 0.f), Vector(38.f, 37.f), Vector(37.f, 0.f), 0.08f, 7);
	m_pAnimator->CreateAnimation(L"IdleLeft", m_pIdleImage, Vector(0.f, 0.f), Vector(38.f, 37.f), Vector(37.f, 0.f), 0.08f, 7);


	m_pAnimator->Play(L"IdleRight", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(30, 30), Vector(0, 0));

}

void KirbyEat::Update()
{
	if (BUTTONUP('S'))
	{
		// 플레이어에 있는 샷 이랑 먹는거 여기로 가져오면 될듯
		DELETEOBJECT(this);

	}
}

void KirbyEat::Render()
{
}

void KirbyEat::Release()
{
}

void KirbyEat::AnimatorUpdate()
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

	if (BUTTONDOWN('S')) str += L"Attack";


	m_pAnimator->Play(str, false);
}

void KirbyEat::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}


void KirbyEat::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"몬스터")
	{

	}
}




void KirbyEat::OnCollisionStay(CCollider* pOtherCollider)
{

}

void KirbyEat::OnCollisionExit(CCollider* pOtherCollider)
{
	
}
