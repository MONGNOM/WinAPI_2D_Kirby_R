#include "framework.h"
#include "CMonster.h"

#include "CRenderManager.h"
#include "CCollider.h"
#include "CPlayer.h"
#include "CImage.h"
#include "CAnimator.h"

CMonster::CMonster()
{
	m_strName = L"몬스터";
	m_vecScale = Vector(100, 100);
	m_layer = Layer::Monster;
	m_vecDir = Vector(0, 0);
	m_fVelocity = 300;
	m_mMoveImage = nullptr;
	m_mDieImage = nullptr;
	m_vecMoveDir = Vector(0, 0);
	m_vecLookDir = Vector(0, -1);
	m_bIsMove = false;
	m_mHp = 1;
	DieTime = 0;
	HP = false;
	Iscrash = false;
	slide = false;
	slideTime = 0;
	
}

CMonster::~CMonster()
{
}

void CMonster::Init()
{
	m_mMoveImage = RESOURCE->LoadImg(L"BasicMonsterMove", L"Image\\Monster\\BasicMonster\\BasicMonster.png");
	m_mDieImage = RESOURCE->LoadImg(L"BasicMonsterDie", L"Image\\Monster\\BasicMonster\\BasicMonsterDie.png");



	m_pAnimator = new CAnimator;


	m_pAnimator->CreateAnimation(L"IdleLeft", m_mMoveImage, Vector(0.f, 100.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.15f, 6);
	m_pAnimator->CreateAnimation(L"IdleRight", m_mMoveImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.15f, 6);
	m_pAnimator->CreateAnimation(L"MoveRight", m_mMoveImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.15f, 6);
	m_pAnimator->CreateAnimation(L"MoveLeft", m_mMoveImage, Vector(0.f, 100.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.15f, 6);

	m_pAnimator->CreateAnimation(L"IdleLeftDie", m_mDieImage, Vector(0.f, 100.f), Vector(60.f, 60.f), Vector(60.f, 0.f), 1.f, 2);
	m_pAnimator->CreateAnimation(L"IdleRightDie", m_mDieImage, Vector(0.f, 0.f), Vector(60.f, 60.f), Vector(60.f, 0.f), 0.5f, 2);
	m_pAnimator->CreateAnimation(L"MoveRightDie", m_mDieImage, Vector(0.f, 0.f), Vector(60.f, 60.f), Vector(60.f, 0.f), 0.5f, 2);
	m_pAnimator->CreateAnimation(L"MoveLeftDie", m_mDieImage, Vector(0.f, 100.f), Vector(60.f, 60.f), Vector(60.f, 0.f), 0.5f, 2);


	m_pAnimator->Play(L"IdleLeft", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(45, 45), Vector(0, 10));
}

void CMonster::Update()
{
	Gravity();

	m_vecPos += m_vecDir * m_fVelocity * DT;

	if (Iscrash == true)
	{
		DieTime += DT;
		//if (DieTime >= 0.1)
		//{
		//	str = L"IdleLeftDie";
		//}
		if (DieTime >= 1)
		{
			DELETEOBJECT(this);
			DieTime = 0;
		}
	}

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
}



void CMonster::Gravity()
{
	if (m_Gravity == true)
	{
		m_vecPos.y += m_fSpeed * DT * 2;
	}


}


void CMonster::Render()
{

}

void CMonster::Release()
{
}

void CMonster::AnimatorUpdate()
{
	if (m_vecMoveDir.Length() > 0)
		m_vecLookDir = m_vecMoveDir;


	if (m_bIsMove)	str += L"Move";
	else			str += L"Idle";

	if (m_vecLookDir.x > 0) str += L"Right";
	else if (m_vecLookDir.x < 0) str += L"Left";

	if (m_mHp == 0) str = L"IdleLeftDie";

	m_pAnimator->Play(str, false);
}

void CMonster::OnCollisionEnter(CCollider* pOtherCollider)
{
	
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		Logger::Debug(L"몬스터가 플레이어와 부딪혀 데미지를 입습니다.");
	
		m_mHp -= 1;
		Iscrash = true;
		HP = true;
		slide = true;
	}

	if (pOtherCollider->GetObjName() == L"빛 공격")
	{
		Logger::Debug(L"몬스터가 빛공격을 맞았습니다.");
		slide = true;
		Iscrash = true;

	}

	if (pOtherCollider->GetObjName() == L"먹기")
	{
		Logger::Debug(L"몬스터가 빨려가기 시작합니다.");
		CGameObject* pl = pOtherCollider->GetOwner();
		if(pl->GetPos().x <= m_vecPos.x )
			SetDir(Vector(-1, 0));
		else if (pl->GetPos().x >= m_vecPos.x)
			SetDir(Vector(1, 0));	
	}


	if (pOtherCollider->GetObjName() == L"Shot")
	{
		Logger::Debug(L"몬스터가 미사일에 맞았습니다");
		DELETEOBJECT(this);
	}
	if (pOtherCollider->GetObjName() == L"땅")
	{

		m_Gravity = false;
	}
}

void CMonster::OnCollisionStay(CCollider* pOtherCollider)
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

void CMonster::OnCollisionExit(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"먹기")
	{
		CGameObject* eat = pOtherCollider->GetOwner();
		Logger::Debug(L"!@!@!@!2몬스터를 먹는다아아아!@!@!@!@");
		DELETEOBJECT(this);

	}


}

void CMonster::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}

void CMonster::SetVelocity(float velocity)
{
	m_fVelocity = velocity;
}
