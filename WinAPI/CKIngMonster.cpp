#include "framework.h"
#include "CKIngMonster.h"

#include "CCollider.h"
#include "CPlayer.h"

CKIngMonster::CKIngMonster()
{

	m_strName = L"보스 몬스터";
	m_vecScale = Vector(100, 100);
	m_layer = Layer::SpecialMonster;
	m_vecDir = Vector(0, 0);
	m_fVelocity = 300;
	m_mMoveImage = nullptr;
	m_mDieImage = nullptr;
	m_vecMoveDir = Vector(0, 0);
	m_vecLookDir = Vector(0, -1);
	m_bIsMove = false;
	m_mHp = 3;
	DieTime = 0;
	Iscrash = false;
	m_mAttackImage = nullptr;
}

CKIngMonster::~CKIngMonster()
{

}

void CKIngMonster::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();

}

void CKIngMonster::SetVelocity(float velocity)
{
	m_fVelocity = velocity;

}

void CKIngMonster::Init()
{

	m_mMoveImage = RESOURCE->LoadImg(L"KingMonsterMove", L"Image\\Monster\\King\\KingisBack.png");
	m_mAttackImage = RESOURCE->LoadImg(L"KingMonsterAttack", L"Image\\Monster\\King\\KingJump.png");
	m_mDieImage = RESOURCE->LoadImg(L"KingMonsterDie", L"Image\\Monster\\King\\KingDie.png");


	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"IdleLeft", m_mMoveImage, Vector(1358.f, 400.f), Vector(162.f, 200.f), Vector(-194.f, 0.f), 0.15f, 8);
	m_pAnimator->CreateAnimation(L"IdleRight", m_mMoveImage, Vector(0.f, 0.f), Vector(162.f, 183.f), Vector(190.f, 0.f), 0.15f, 8);
	m_pAnimator->CreateAnimation(L"MoveRight", m_mMoveImage, Vector(0.f, 0.f), Vector(162.f, 183.f), Vector(190.f, 0.f), 0.15f, 8);
	m_pAnimator->CreateAnimation(L"MoveLeft", m_mMoveImage, Vector(1358.f, 400.f), Vector(162.f, 200.f), Vector(-190.f, 0.f), 0.15f, 8);

	m_pAnimator->CreateAnimation(L"IdleLeftDie", m_mDieImage, Vector(0.f, 100.f), Vector(60.f, 60.f), Vector(60.f, 0.f), 1.f, 2);
	m_pAnimator->CreateAnimation(L"IdleRightDie", m_mDieImage, Vector(0.f, 0.f), Vector(60.f, 60.f), Vector(60.f, 0.f), 1.f, 2);
	m_pAnimator->CreateAnimation(L"MoveRightDie", m_mDieImage, Vector(0.f, 0.f), Vector(60.f, 60.f), Vector(60.f, 0.f), 1.f, 2);
	m_pAnimator->CreateAnimation(L"MoveLeftDie", m_mDieImage, Vector(0.f, 100.f), Vector(60.f, 60.f), Vector(60.f, 0.f), 1.f, 2);


	m_pAnimator->Play(L"IdleLeft", false);
	AddComponent(m_pAnimator);


	AddCollider(ColliderType::Rect, Vector(150, 150), Vector(0, 30));
}

void CKIngMonster::Update()
{

	if (m_mHp == 0)
	{
		Iscrash = true;
	}
	Gravity();

	m_vecPos += m_vecDir * m_fVelocity * DT;

	if (Iscrash == true)
	{
		DieTime += DT;
		if (DieTime >= 1)
		{
			DELETEOBJECT(this);
			DieTime = 0;
		}
	}
}

void CKIngMonster::Render()
{
}

void CKIngMonster::Release()
{
}

void CKIngMonster::Gravity()
{
	if (m_Gravity == true)
	{
		m_vecPos.y += m_fSpeed * DT * 2;
	}
}

void CKIngMonster::AnimatorUpdate()
{
	if (m_vecMoveDir.Length() > 0)
		m_vecLookDir = m_vecMoveDir;

	wstring str = L"";

	if (m_bIsMove)	str += L"Move";
	else			str += L"Idle";

	if (m_vecLookDir.x > 0) str += L"Right";
	else if (m_vecLookDir.x < 0) str += L"Left";

	if (m_mHp == 0) str += L"Die";

	m_pAnimator->Play(str, false);
}

void CKIngMonster::OnCollisionEnter(CCollider* pOtherCollider)
{


	if (pOtherCollider->GetObjName() == L"빛 공격")
	{
		Logger::Debug(L"몬스터가 빛공격을 맞았습니다.");
		CGameObject* pl = pOtherCollider->GetOwner();
		if (pl->GetPos().x <= m_vecPos.x)
			m_vecPos.x += 50;
		else if (pl->GetPos().x >= m_vecPos.x)
			m_vecPos.x -= 50;
		
		m_mHp -= 1;

	}

	if (pOtherCollider->GetObjName() == L"먹기")
	{
		Logger::Debug(L"몬스터가 빨려가기 시작합니다.");
		CGameObject* pl = pOtherCollider->GetOwner();
		if (pl->GetPos().x <= m_vecPos.x)
			SetDir(Vector(-1, 0));
		else if (pl->GetPos().x >= m_vecPos.x)
			SetDir(Vector(1, 0));

	}

	if (pOtherCollider->GetObjName() == L"Shot")
	{
		Logger::Debug(L"몬스터가 미사일에 맞았습니다");
		m_mHp -= 1;
	}
	if (pOtherCollider->GetObjName() == L"땅")
	{
		m_Gravity = false;
	}
}

void CKIngMonster::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"먹기")
	{
		Logger::Debug(L"몬스터가 빨려들어가고있습니다.");
	}
	if (pOtherCollider->GetObjName() == L"땅")
	{

		m_Gravity = false;
	}
}

void CKIngMonster::OnCollisionExit(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"먹기")
	{
		Logger::Debug(L"몬스터를 먹었습니다.");
		DELETEOBJECT(this);

	}
}
