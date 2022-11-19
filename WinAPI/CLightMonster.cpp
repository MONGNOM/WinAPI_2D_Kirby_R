#include "framework.h"
#include "CLightMonster.h"

#include "CRenderManager.h"
#include "CCollider.h"
#include "CPlayer.h"

CLightMonster::CLightMonster()
{
	m_strName = L"������";
	m_vecScale = Vector(100, 100);
	m_layer = Layer::SpecialMonster;
	m_vecDir = Vector(0, 0);
	m_fVelocity = 300;
	m_mMoveImage = nullptr;
	m_mDieImage = nullptr;
	m_vecMoveDir = Vector(0, 0);
	m_vecLookDir = Vector(0, -1);
	m_bIsMove = false;
	m_mHp = 1;
	DieTime = 0;
	Iscrash = false;
	m_mAttackImage = nullptr;
	 slide = false;
	 slideTime = 0;
}

CLightMonster::~CLightMonster()
{
}

void CLightMonster::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();

}

void CLightMonster::SetVelocity(float velocity)
{
	m_fVelocity = velocity;

}

void CLightMonster::Init()
{

	m_mMoveImage = RESOURCE->LoadImg(L"BeamMonsterMove", L"Image\\Monster\\BeamMonster\\BeamMonster.png");
	m_mAttackImage = RESOURCE->LoadImg(L"BeamMonsterMoveAttack", L"Image\\Monster\\BeamMonster\\BeamMonsterAttack.png");
	m_mDieImage = RESOURCE->LoadImg(L"BeamMonsterDie", L"Image\\Monster\\BeamMonster\\BeamMonsterDie.png");


	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"IdleLeft", m_mMoveImage, Vector(0.f, 100.f), Vector(50.f, 58.f), Vector(70.f, 0.f), 0.15f, 5);
	m_pAnimator->CreateAnimation(L"IdleRight", m_mMoveImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.15f, 5);
	m_pAnimator->CreateAnimation(L"MoveRight", m_mMoveImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.15f, 6);
	m_pAnimator->CreateAnimation(L"MoveLeft", m_mMoveImage, Vector(0.f, 100.f), Vector(50.f, 58.f), Vector(70.f, 0.f), 0.15f, 6);

	m_pAnimator->CreateAnimation(L"IdleLeftDie", m_mDieImage, Vector(0.f, 100.f), Vector(60.f, 60.f), Vector(60.f, 0.f), 1.f, 2);
	m_pAnimator->CreateAnimation(L"IdleRightDie", m_mDieImage, Vector(0.f, 0.f), Vector(60.f, 60.f), Vector(60.f, 0.f), 1.f, 2);
	m_pAnimator->CreateAnimation(L"MoveRightDie", m_mDieImage, Vector(0.f, 0.f), Vector(60.f, 60.f), Vector(60.f, 0.f),	1.f, 2);
	m_pAnimator->CreateAnimation(L"MoveLeftDie", m_mDieImage, Vector(0.f, 100.f), Vector(60.f, 60.f), Vector(60.f, 0.f), 1.f, 2);


	m_pAnimator->Play(L"IdleLeft", false);
	AddComponent(m_pAnimator);


	AddCollider(ColliderType::Rect, Vector(45, 45), Vector(0, 10));

}

void CLightMonster::Update()
{

	if (slide == true)
	{
		slideTime += DT;
		if (slideTime <= 0.1f)
		{
			if (GAME->PlayerPos.x <= m_vecPos.x)
				m_vecPos.x += m_fSpeed * DT * 3;

			else if (GAME->PlayerPos.x >= m_vecPos.x)
				m_vecPos.x -= m_fSpeed * DT * 3;

			slideTime = 0;
		}
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

void CLightMonster::Render()
{

}

void CLightMonster::Release()
{
}

void CLightMonster::Gravity()
{
	if (m_Gravity == true)
	{
		m_vecPos.y += m_fSpeed * DT * 2;
	}
}

void CLightMonster::AnimatorUpdate()
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

void CLightMonster::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"�÷��̾�")
	{
		Logger::Debug(L"���Ͱ� �÷��̾�� �ε��� �������� �Խ��ϴ�.");
		
		m_mHp -= 1;
		Iscrash = true;
		slide = true;
	}

	if (pOtherCollider->GetObjName() == L"�� ����")
	{

		Logger::Debug(L"���Ͱ� �������� �¾ҽ��ϴ�.");
		CGameObject* pl = pOtherCollider->GetOwner();
		slide = true;
		Iscrash = true;

	}

	if (pOtherCollider->GetObjName() == L"�Ա�")
	{
		Logger::Debug(L"���Ͱ� �������� �����մϴ�.");
		CGameObject* pl = pOtherCollider->GetOwner();
		if (pl->GetPos().x <= m_vecPos.x)
			SetDir(Vector(-1, 0));
		else if (pl->GetPos().x >= m_vecPos.x)
			SetDir(Vector(1, 0));

	}

	if (pOtherCollider->GetObjName() == L"Shot")
	{
		Logger::Debug(L"���Ͱ� �̻��Ͽ� �¾ҽ��ϴ�");
		DELETEOBJECT(this);
	}
	if (pOtherCollider->GetObjName() == L"��")
	{

		m_Gravity = false;
	}
}

void CLightMonster::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"�Ա�")
	{
		Logger::Debug(L"���Ͱ� ���������ֽ��ϴ�.");
	}
	if (pOtherCollider->GetObjName() == L"��")
	{

		m_Gravity = false;
	}
}

void CLightMonster::OnCollisionExit(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"�Ա�")
	{
		Logger::Debug(L"���͸� �Ծ����ϴ�.");
		DELETEOBJECT(this);

	}
}
