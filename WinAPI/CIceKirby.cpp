#include "framework.h"
#include "CIceKirby.h"

#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"
#include "CMonster.h"

#include "CMissile.h"
#include "KirbyEat.h"
#include "KirbyShot.h"
#include "LightKirbyShot.h"
#include "CIceKirbyShot.h"


CIceKirby::CIceKirby()
{
	ontile = 0;
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(100, 100);
	m_layer = Layer::Player;
	m_strName = L"플레이어";
	m_vecMoveDir = Vector(0, 0);
	m_vecLookDir = Vector(0, -1);
	m_bIsMove = false;
	Jumpgo = false;
	JumpTime = 0.f;
	LastJumpTime = 0.f;
	LastRunTime;
	m_Gravity = true;
	m_pChangeImage = nullptr;

	m_pHp = 3;
	m_pIdleImageR = nullptr;
	m_pIdleImageU = nullptr;
	m_pIdleImageL = nullptr;
	m_pMoveImage = nullptr;
	m_pAttackImage = nullptr;
	m_pRunImageR = nullptr;
	m_pRunImageL = nullptr;
	m_pIdleImageRD = nullptr;
	m_pIdleImageLD = nullptr;
	m_pAttackImageRD = nullptr;
	m_pAttackImageLD = nullptr;
	m_pJumpImage = nullptr;

	DownAttack = true;
}

CIceKirby::~CIceKirby()
{
}

void CIceKirby::Init()
{
	m_pChangeImage = RESOURCE->LoadImg(L"IcePlayerIdleR", L"Image\\Kirby\\Ice\\IceKirby.png");
	m_pAttackImage = RESOURCE->LoadImg(L"IcePlayerAttack", L"Image\\Kirby\\Ice\\IceKirbyAttackPose.png");


	m_pAttackImageRD = RESOURCE->LoadImg(L"IcePlayerDownAttack", L"Image\\Kirby\\Ice\\IceKirbyDownAttack.png");
	m_pIdleImageR = RESOURCE->LoadImg(L"IcePlayerIdleR", L"Image\\Kirby\\Ice\\IceKirby.png");
	m_pIdleImageRD = RESOURCE->LoadImg(L"IcePlayerDown", L"Image\\Kirby\\Ice\\IceKirbyDown.png");

	m_pIdleImageU = RESOURCE->LoadImg(L"IcePlayerFly", L"Image\\Kirby\\Ice\\IceKirbyFly.png");
	m_pIdleImageL = RESOURCE->LoadImg(L"IcePlayerIdleR", L"Image\\Kirby\\Ice\\IceKirby.png");

	m_pMoveImage = RESOURCE->LoadImg(L"IcePlayerWalk", L"Image\\Kirby\\Ice\\IceKirbyWalk.png");

	m_pJumpImage = RESOURCE->LoadImg(L"IcePlayerJump", L"Image\\Kirby\\Ice\\IceKirbyJump.png");

	m_pRunImageR = RESOURCE->LoadImg(L"IcePlayerRun", L"Image\\Kirby\\Ice\\IceKirbyRun.png");



	m_pAnimator = new CAnimator;

	m_pAnimator->CreateAnimation(L"IdleUPDown", m_pChangeImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 10.0f, 1);
	m_pAnimator->CreateAnimation(L"IdleDownUP", m_pChangeImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 10.0f, 1);

	m_pAnimator->CreateAnimation(L"IdleUp", m_pIdleImageU, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 10);
	m_pAnimator->CreateAnimation(L"IdleRightUp", m_pIdleImageU, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 10);
	m_pAnimator->CreateAnimation(L"IdleRight", m_pIdleImageR, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.8f, 2);
	m_pAnimator->CreateAnimation(L"Idle", m_pIdleImageR, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.8f, 2);
	m_pAnimator->CreateAnimation(L"IdleRightDown", m_pIdleImageRD, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.8f, 2);
	m_pAnimator->CreateAnimation(L"IdleDown", m_pIdleImageRD, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(43.f, 0.f), 0.8f, 2);
	m_pAnimator->CreateAnimation(L"IdleLeft", m_pIdleImageR, Vector(70.f, 100.f), Vector(50.f, 50.f), Vector(-70.f, 0.f), 0.8f, 2);
	m_pAnimator->CreateAnimation(L"IdleLeftDown", m_pIdleImageRD, Vector(70.f, 100.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.8f, 2);
	m_pAnimator->CreateAnimation(L"IdleLeftUp", m_pIdleImageU, Vector(620.f, 100.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.08f, 10);


	m_pAnimator->CreateAnimation(L"IdleRightDownRun", m_pIdleImageRD, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.8f, 2);
	m_pAnimator->CreateAnimation(L"MoveRightDownRun", m_pIdleImageRD, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.8f, 2);
	m_pAnimator->CreateAnimation(L"MoveLeftDownRun", m_pIdleImageRD, Vector(80.f, 100.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.8f, 2);
	m_pAnimator->CreateAnimation(L"IdleLeftDownRun", m_pIdleImageRD, Vector(80.f, 100.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.8f, 2);


	m_pAnimator->CreateAnimation(L"MoveUp", m_pIdleImageU, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 10);
	m_pAnimator->CreateAnimation(L"MoveRight", m_pMoveImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);
	m_pAnimator->CreateAnimation(L"MoveRightUp", m_pIdleImageU, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 10);
	m_pAnimator->CreateAnimation(L"MoveRightDown", m_pIdleImageRD, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.8f, 2);
	m_pAnimator->CreateAnimation(L"MoveLeftDown", m_pIdleImageRD, Vector(80.f, 100.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.8f, 2);
	m_pAnimator->CreateAnimation(L"MoveLeft", m_pMoveImage, Vector(630.f, 100.f), Vector(50.f, 50.f), Vector(-70.f, 0.f), 0.05f, 10);
	m_pAnimator->CreateAnimation(L"MoveLeftUp", m_pIdleImageU, Vector(620.f, 100.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.08f, 10);

	m_pAnimator->CreateAnimation(L"IdleAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 10);
	m_pAnimator->CreateAnimation(L"IdleUpAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 10);
	m_pAnimator->CreateAnimation(L"IdleRightUpAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.80f, 10);
	m_pAnimator->CreateAnimation(L"IdleRightAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 10);
	m_pAnimator->CreateAnimation(L"IdleLeftUpAttack", m_pAttackImage, Vector(630.f, 100.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.08f, 10);
	m_pAnimator->CreateAnimation(L"IdleLeftAttack", m_pAttackImage, Vector(630.f, 100.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.08f, 10);
	m_pAnimator->CreateAnimation(L"IdleRightDownAttack", m_pAttackImageRD, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.5f, 2);
	m_pAnimator->CreateAnimation(L"IdleDownAttack", m_pAttackImageRD, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.5f, 2);
	m_pAnimator->CreateAnimation(L"IdleLeftDownAttack", m_pAttackImageRD, Vector(70.f, 100.f), Vector(50.f, 50.f), Vector(-70.f, 0.f), 0.5f, 2);

	m_pAnimator->CreateAnimation(L"MoveRightAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 10);
	m_pAnimator->CreateAnimation(L"MoveLeftAttack", m_pAttackImage, Vector(630.f, 100.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.08f, 10);
	m_pAnimator->CreateAnimation(L"MoveUpAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 10);
	m_pAnimator->CreateAnimation(L"MoveDownLeftAttack", m_pAttackImageRD, Vector(70.f, 100.f), Vector(50.f, 50.f), Vector(-70.f, 0.f), 0.5f, 2);
	m_pAnimator->CreateAnimation(L"MoveAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 10);


	m_pAnimator->CreateAnimation(L"IdleRun", m_pRunImageR, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 8);
	m_pAnimator->CreateAnimation(L"IdleRightRun", m_pRunImageR, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 8);
	m_pAnimator->CreateAnimation(L"IdleLeftRun", m_pRunImageR, Vector(490.f, 104.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.05f, 8);

	m_pAnimator->CreateAnimation(L"MoveUpRun", m_pRunImageR, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 8);
	m_pAnimator->CreateAnimation(L"MoveRightRun", m_pRunImageR, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 8);
	m_pAnimator->CreateAnimation(L"MoveLeftRun", m_pRunImageR, Vector(490.f, 104.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.05f, 8);


	m_pAnimator->CreateAnimation(L"MoveRightAttackRun", m_pAttackImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 10);
	m_pAnimator->CreateAnimation(L"MoveLeftAttackRun", m_pAttackImage, Vector(630.f, 100.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 10);
	m_pAnimator->CreateAnimation(L"MoveUpAttackRun", m_pAttackImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 10);


	m_pAnimator->CreateAnimation(L"IdleJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.08f, 10);
	m_pAnimator->CreateAnimation(L"IdleRightJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.08f, 10);
	m_pAnimator->CreateAnimation(L"IdleLeftJump", m_pJumpImage, Vector(630.f, 100.f), Vector(50.f, 50.f), Vector(-70.f, 0.f), 0.08f, 10);
	m_pAnimator->CreateAnimation(L"IdleRightRunJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.08f, 10);
	m_pAnimator->CreateAnimation(L"IdleLeftRunJump", m_pJumpImage, Vector(630.f, 100.f), Vector(50.f, 50.f), Vector(-70.f, 0.f), 0.08f, 10);
	

	m_pAnimator->CreateAnimation(L"MoveRightJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.08f, 10);
	m_pAnimator->CreateAnimation(L"MoveRightUpJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.08f, 10);
	m_pAnimator->CreateAnimation(L"MoveLeftJump", m_pJumpImage, Vector(630.f, 100.f), Vector(50.f, 50.f), Vector(-70.f, 0.f), 0.08f, 10);
	m_pAnimator->CreateAnimation(L"MoveLeftUpJump", m_pJumpImage, Vector(630.f, 100.f), Vector(50.f, 50.f), Vector(-70.f, 0.f), 0.08f, 10);

	m_pAnimator->CreateAnimation(L"MoveRightRunJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.08f, 10);
	m_pAnimator->CreateAnimation(L"MoveRightUpRunJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.08f, 10);
	m_pAnimator->CreateAnimation(L"MoveLeftRunJump", m_pJumpImage, Vector(630.f, 100.f), Vector(50.f, 50.f), Vector(-70.f, 0.f), 0.08f, 10);
	m_pAnimator->CreateAnimation(L"MoveLeftUpRunJump", m_pJumpImage, Vector(630.f, 100.f), Vector(50.f, 50.f), Vector(-70.f, 0.f), 0.08f, 10);


	m_pAnimator->CreateAnimation(L"IdleAttackJump", m_pAttackImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 10);
	m_pAnimator->CreateAnimation(L"IdleRightAttackJump", m_pAttackImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 10);
	m_pAnimator->CreateAnimation(L"IdleLeftAttackJump", m_pAttackImage, Vector(630.f, 100.f), Vector(50.f, 50.f), Vector(-70.f, 0.f), 0.08f, 10);
	m_pAnimator->CreateAnimation(L"MoveRightAttackJump", m_pAttackImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 10);
	m_pAnimator->CreateAnimation(L"MoveLeftAttackJump", m_pAttackImage, Vector(630.f, 100.f), Vector(50.f, 50.f), Vector(-70.f, 0.f), 0.08f, 10);
	m_pAnimator->CreateAnimation(L"MoveAttackJump", m_pAttackImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 10);

	m_pAnimator->Play(L"IdleRight", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(50, 55), Vector(0, 0));

}

void CIceKirby::Update()
{

	GAME->PlayerPos = m_vecPos;
	Gravity();
	m_bIsMove = false;

	if (m_pHp <= 0)
	{
		DELETEOBJECT(this);
	}

	if (BUTTONSTAY(VK_DOWN) && BUTTONDOWN('S'))
	{
		DownAttack = false;
	}
	if (DownAttack == false)
	{
		m_vecPos.x += m_fSpeed * DT + 100;
		DownAttack = true;
		// 시간 넣어서 그 시간만큼 이 거리를 이동하게 끔 설정
	}
	if (BUTTONSTAY(VK_LEFT))
	{
		LastRunTime += DT;
		if (BUTTONSTAY('R')/*LastRunTime <= 0.15f && BUTTONSTAY(VK_LEFT)*/)
		{
			m_vecPos.x -= m_fSpeed * DT * 2.f;
			m_bIsMove = true;
			m_vecMoveDir.x = -1;
			LastRunTime = 0;
		}
		else if (BUTTONSTAY(VK_DOWN))
		{
			m_vecMoveDir.x = -1;
			m_bIsMove = false;
		}
		else if (BUTTONSTAY('S'))
		{
			m_vecMoveDir.x = 0;
			m_bIsMove = false;
		}
		else
		{
			m_vecPos.x -= m_fSpeed * DT;
			m_bIsMove = true;
			m_vecMoveDir.x = -1;
		}
	}

	else if (BUTTONSTAY(VK_RIGHT))
	{

		if (BUTTONSTAY('R')/*LastRunTime <= 0.15f && BUTTONSTAY(VK_RIGHT)*/)
		{
			m_vecPos.x += m_fSpeed * DT * 2.f;
			m_bIsMove = true;
			m_vecMoveDir.x = +1;
			LastRunTime = 0;
		}
		else if (BUTTONSTAY('S'))
		{
			m_vecMoveDir.x = 0;
			m_bIsMove = false;
		}
		else if (BUTTONSTAY(VK_DOWN))/*LastRunTime <= 0.15f && BUTTONSTAY(VK_LEFT)*/
		{
			m_vecMoveDir.x = +1;
			m_bIsMove = false;
		}
		else
		{
			m_vecPos.x += m_fSpeed * DT;
			m_bIsMove = true;
			m_vecMoveDir.x = +1;
		}
	}


	if (BUTTONDOWN('D'))
	{
		Logger::Debug(L"특수능력을 뱉었다");
		BasicKirby();
	}

	if (BUTTONDOWN('S') && DownAttack == true)
	{
		Logger::Debug(L"얼음 공격");
		IceAttack();

	}

	if (BUTTONDOWN('A'))
	{
		Jumpgo = true;
	}

	if (BUTTONSTAY(VK_UP))
	{
		JumpTime += DT;

		if (JumpTime <= 0.3f)
		{
			Logger::Debug(L"점프");
			m_vecPos.y -= m_fSpeed * DT * 3.;
		}
		else
		{
			JumpTime = 0;
			Jumpgo = false;
		}
	}
	if (Jumpgo == true)
	{
		JumpTime += DT;

		if (JumpTime <= 0.3f)
		{
			Logger::Debug(L"점프");
			m_vecPos.y -= m_fSpeed * DT * 4;
		}
		else
		{
			JumpTime = 0;
			Jumpgo = false;
		}
	}

	AnimatorUpdate();

}

void CIceKirby::Render()
{
}

void CIceKirby::Release()
{
}

void CIceKirby::BasicKirby()
{
	Logger::Debug(L"커비가 능력을 뱉었다.");

	CGameObject* BasicKirby = new CPlayer;
	BasicKirby->SetPos(GAME->PlayerPos);
	ADDOBJECT(BasicKirby);

	DELETEOBJECT(this);

}

void CIceKirby::Gravity()
{

	if (m_Gravity == true)
		m_vecPos.y += m_fSpeed * DT * 2;
}

void CIceKirby::AnimatorUpdate()
{

	if (m_vecMoveDir.Length() > 0)
		m_vecLookDir = m_vecMoveDir;

	wstring str = L"";

	if (m_bIsMove)	str += L"Move";
	else			str += L"Idle";

	if (m_vecLookDir.x > 0) str += L"Right";
	else if (m_vecLookDir.x < 0) str += L"Left";


	if (BUTTONSTAY(VK_UP)) str += L"Up";
	if (BUTTONSTAY(VK_DOWN)) str += L"Down";

	/*if (m_vecLookDir.y > 0) str += L"flying";
	else if (m_vecLookDir.y < 0) str += L"jumping";*/


	if (BUTTONSTAY('S')) str += L"Attack";

	if (BUTTONSTAY('R')) str += L"Run";

	if (BUTTONSTAY('A')) str += L"Jump";


	m_pAnimator->Play(str, false);
}

void CIceKirby::IceAttack()
{

	if (DownAttack == true)
	{
		CIceKirbyShot* IceAttack = new CIceKirbyShot;
		if (m_vecLookDir.x > 0)
			IceAttack->SetPos(m_vecPos.x + 45, GetPos().y);
		else if (m_vecLookDir.x < 0)
			IceAttack->SetPos(m_vecPos.x - 45, GetPos().y);

		IceAttack->SetDir(Vector(m_vecPos.x +200, m_vecMoveDir.y));
		ADDOBJECT(IceAttack);
	}
}

void CIceKirby::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"몬스터")
	{
		Logger::Debug(L"몬스터와 부딪혀 데미지를 입습니다.");
		m_pHp = -1;
		CGameObject* pl = pOtherCollider->GetOwner();
		if (pl->GetPos().x <= m_vecPos.x)
			m_vecPos.x += 20;
		else if (pl->GetPos().x >= m_vecPos.x)
			m_vecPos.x -= 20;
	}

	if (pOtherCollider->GetObjName() == L"빛몬스터")
	{
		Logger::Debug(L"몬스터와 부딪혀 데미지를 입습니다.");
		m_pHp = -1;
		CGameObject* pl = pOtherCollider->GetOwner();
		if (pl->GetPos().x <= m_vecPos.x)
			m_vecPos.x += 20;
		else if (pl->GetPos().x >= m_vecPos.x)
			m_vecPos.x -= 20;

	}

	if (pOtherCollider->GetObjName() == L"얼음 몬스터")
	{
		Logger::Debug(L"몬스터와 부딪혀 데미지를 입습니다.");
		m_LightChange = false;
		m_Eat = false;
		m_pHp -= 1;
		CGameObject* pl = pOtherCollider->GetOwner();
		if (pl->GetPos().x <= m_vecPos.x)
			m_vecPos.x += 20;
		else if (pl->GetPos().x >= m_vecPos.x)
			m_vecPos.x -= 20;
	}

	if (pOtherCollider->GetObjName() == L"보스 몬스터")
	{
		Logger::Debug(L"몬스터와 부딪혀 데미지를 입습니다.");
		m_pHp = -1;
		CGameObject* pl = pOtherCollider->GetOwner();
		if (pl->GetPos().x <= m_vecPos.x)
			m_vecPos.x += 20;
		else if (pl->GetPos().x >= m_vecPos.x)
			m_vecPos.x -= 20;

	}

	if (pOtherCollider->GetObjName() == L"땅")
	{
		if (ontile >= 1)
			m_Gravity = false;
		++ontile;
	}
}

void CIceKirby::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"땅")
	{
		if (ontile >= 1)
			m_Gravity = false;
	}
}

void CIceKirby::OnCollisionExit(CCollider* pOtherCollider)
{

	if (pOtherCollider->GetObjName() == L"땅")
	{
		--ontile;
		if (ontile == 0)
		{
			m_Gravity = true;
		}
	}
}
