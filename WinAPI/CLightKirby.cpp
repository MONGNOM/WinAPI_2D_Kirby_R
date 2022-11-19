#include "framework.h"
#include "CLightKirby.h"

#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"
#include "CMonster.h"

#include "CMissile.h"
#include "KirbyEat.h"
#include "KirbyShot.h"
#include "LightKirbyShot.h"

CLightKirby::CLightKirby()
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
	m_pMoveImageR = nullptr;
	m_pMoveImageL = nullptr;
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

CLightKirby::~CLightKirby()
{
}

void CLightKirby::Init()
{

	m_pChangeImage = RESOURCE->LoadImg(L"LightPlayerChange", L"Image\\Kirby\\Light\\LightKirbyChange.png");
	m_pAttackImage = RESOURCE->LoadImg(L"LightPlayerAttack", L"Image\\Kirby\\Light\\LightKirbyAttack.png");


	m_pAttackImage = RESOURCE->LoadImg(L"LightPlayerAttack", L"Image\\Kirby\\Light\\LightKirby.png");

	m_pAttackImageRD = RESOURCE->LoadImg(L"LightPlayerDownAttackR", L"Image\\Kirby\\Light\\LightKirbyDownAttack.png");
	m_pIdleImageR = RESOURCE->LoadImg(L"LightPlayerIdleR", L"Image\\Kirby\\Light\\LightKirby.png");
	m_pIdleImageRD = RESOURCE->LoadImg(L"LightPlayerIdleRD", L"Image\\Kirby\\Light\\LightKirbyDown.png");
	m_pIdleImageLD = RESOURCE->LoadImg(L"LightPlayerIdleLD", L"Image\\Kirby\\Light\\LightKirbyDownLeft.png");

	m_pIdleImageU = RESOURCE->LoadImg(L"LightPlayerIdleU", L"Image\\Kirby\\Light\\LightKirbyFly.png");
	m_pIdleImageL = RESOURCE->LoadImg(L"LightPlayerIdleL", L"Image\\Kirby\\Light\\LightKirbyChange.png");

	m_pMoveImageR = RESOURCE->LoadImg(L"LightPlayerMoveR", L"Image\\Kirby\\Light\\LightKirbyWalk.png");
	m_pMoveImageL = RESOURCE->LoadImg(L"LightPlayerMoveL", L"Image\\Kirby\\Light\\LightKirbyWalk.png");

	m_pJumpImage = RESOURCE->LoadImg(L"LightPlayerJump", L"Image\\Kirby\\Light\\LightKirbyJump.png");

	m_pRunImageR = RESOURCE->LoadImg(L"LightPlayerRunR", L"Image\\Kirby\\Light\\LightKirbyRun.png");
	m_pRunImageL = RESOURCE->LoadImg(L"LightPlayerRunL", L"Image\\Kirby\\Light\\LightKirbyRun.png");



	m_pAnimator = new CAnimator;

	m_pAnimator->CreateAnimation(L"IdleUPDown", m_pChangeImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 10.0f, 1);
	m_pAnimator->CreateAnimation(L"IdleDownUP", m_pChangeImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 10.0f, 1);

	m_pAnimator->CreateAnimation(L"IdleUp", m_pIdleImageU, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 11);
	m_pAnimator->CreateAnimation(L"IdleRightUp", m_pIdleImageU, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 11);
	m_pAnimator->CreateAnimation(L"IdleRight", m_pIdleImageR, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(71.f, 0.f), 0.8f, 2);
	m_pAnimator->CreateAnimation(L"Idle", m_pIdleImageR, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(71.f, 0.f), 0.8f, 2);
	m_pAnimator->CreateAnimation(L"IdleRightDown", m_pIdleImageRD, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(43.f, 0.f), 10.0f, 1);
	m_pAnimator->CreateAnimation(L"IdleDown", m_pIdleImageRD, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(50.f, 0.f), 10.0f, 1);
	m_pAnimator->CreateAnimation(L"IdleLeft", m_pIdleImageR, Vector(75.f, 100.f), Vector(50.f, 50.f), Vector(-71.f, 0.f), 0.8f, 2);
	m_pAnimator->CreateAnimation(L"IdleLeftDown", m_pIdleImageLD, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(50.f, 0.f), 10.0f, 1);
	m_pAnimator->CreateAnimation(L"IdleLeftUp", m_pIdleImageU, Vector(700.f, 100.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.08f, 11);


	m_pAnimator->CreateAnimation(L"IdleRightDownRun", m_pIdleImageRD, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(43.f, 0.f), 10.0f, 1);
	m_pAnimator->CreateAnimation(L"MoveRightDownRun", m_pIdleImageRD, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);
	m_pAnimator->CreateAnimation(L"MoveLeftDownRun", m_pIdleImageLD, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(50.f, 0.f), 10.0f, 1);
	m_pAnimator->CreateAnimation(L"IdleLeftDownRun", m_pIdleImageLD, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(50.f, 0.f), 10.0f, 1);


	m_pAnimator->CreateAnimation(L"MoveUp", m_pIdleImageU, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 20);
	m_pAnimator->CreateAnimation(L"MoveRight", m_pMoveImageR, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);
	m_pAnimator->CreateAnimation(L"MoveRightUp", m_pIdleImageU, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 11);
	m_pAnimator->CreateAnimation(L"MoveRightDown", m_pIdleImageRD, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 1);
	m_pAnimator->CreateAnimation(L"MoveLeftDown", m_pIdleImageLD, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(50.f, 0.f), 10.f, 1);
	m_pAnimator->CreateAnimation(L"MoveLeft", m_pMoveImageL, Vector(700.f, 100.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.05f, 10);
	m_pAnimator->CreateAnimation(L"MoveLeftUp", m_pIdleImageU, Vector(700.f, 100.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.08f, 11);

	m_pAnimator->CreateAnimation(L"IdleAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(132.f, 132.f), Vector(150.f, 0.f), 0.02f, 35);
	m_pAnimator->CreateAnimation(L"IdleUpAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(132.f, 132.f), Vector(150.f, 0.f), 0.02f, 35);
	m_pAnimator->CreateAnimation(L"IdleRightUpAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(132.f, 132.f), Vector(150.f, 0.f), 0.02f, 35);
	m_pAnimator->CreateAnimation(L"IdleRightAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(132.f, 132.f), Vector(150.f, 0.f), 0.02f, 35);
	m_pAnimator->CreateAnimation(L"IdleLeftUpAttack", m_pAttackImage, Vector(5070.f, 142.f), Vector(132.f, 132.f), Vector(-150.f, 0.f), 0.02f, 35);
	m_pAnimator->CreateAnimation(L"IdleLeftAttack", m_pAttackImage, Vector(5070.f, 142.f), Vector(132.f, 132.f), Vector(-150.f, 0.f), 0.02f, 35);
	m_pAnimator->CreateAnimation(L"IdleRightDownAttack", m_pAttackImageRD, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.5f, 3);
	m_pAnimator->CreateAnimation(L"IdleDownAttack", m_pAttackImageRD, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.5f, 3);
	m_pAnimator->CreateAnimation(L"IdleLeftDownAttack", m_pAttackImageRD, Vector(150.f, 100.f), Vector(50.f, 50.f), Vector(-70.f, 0.f), 0.5f, 3);

	m_pAnimator->CreateAnimation(L"MoveRightAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(132.f, 132.f), Vector(150.f, 0.f), 0.02f, 35);
	m_pAnimator->CreateAnimation(L"MoveLeftAttack", m_pAttackImage, Vector(5070.f, 142.f), Vector(132.f, 132.f), Vector(-150.f, 0.f), 0.02f, 35);
	m_pAnimator->CreateAnimation(L"MoveUpAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(132.f, 132.f), Vector(150.f, 0.f), 0.02f, 35);
 	m_pAnimator->CreateAnimation(L"MoveDownLeftAttack", m_pAttackImageRD, Vector(150.f, 100.f), Vector(50.f, 50.f), Vector(-70.f, 0.f), 0.5f, 3);
	m_pAnimator->CreateAnimation(L"MoveAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(132.f, 132.f), Vector(150.f, 0.f), 0.02f, 35);


	m_pAnimator->CreateAnimation(L"IdleRun", m_pRunImageR, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 8);
	m_pAnimator->CreateAnimation(L"IdleRightRun", m_pRunImageR, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 8);
	m_pAnimator->CreateAnimation(L"IdleLeftRun", m_pRunImageR, Vector(490.f, 104.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.05f, 8);

	m_pAnimator->CreateAnimation(L"MoveUpRun", m_pRunImageR, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 8);
	m_pAnimator->CreateAnimation(L"MoveRightRun", m_pRunImageR, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 8);
	m_pAnimator->CreateAnimation(L"MoveLeftRun", m_pRunImageR, Vector(490.f, 104.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.05f, 8);


	m_pAnimator->CreateAnimation(L"MoveRightAttackRun", m_pAttackImage, Vector(0.f, 0.f), Vector(132.f, 132.f), Vector(150.f, 0.f), 0.02f, 35);
	m_pAnimator->CreateAnimation(L"MoveLeftAttackRun", m_pAttackImage, Vector(5070.f, 142.f), Vector(132.f, 132.f), Vector(-150.f, 0.f), 0.02f, 35);
	m_pAnimator->CreateAnimation(L"MoveUpAttackRun", m_pAttackImage, Vector(0.f, 0.f), Vector(132.f, 132.f), Vector(150.f, 0.f), 0.02f, 35);


	m_pAnimator->CreateAnimation(L"IdleJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.08f, 11);
	m_pAnimator->CreateAnimation(L"IdleRightJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.08f, 11);
	m_pAnimator->CreateAnimation(L"IdleLeftJump", m_pJumpImage, Vector(700.f ,100.f), Vector(50.f, 50.f), Vector(-70.f, 0.f), 0.08f, 11);
	m_pAnimator->CreateAnimation(L"IdleRightRunJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.08f, 11);
	m_pAnimator->CreateAnimation(L"IdleLeftRunJump", m_pJumpImage, Vector(700.f, 100.f), Vector(50.f, 50.f), Vector(-70.f, 0.f), 0.08f, 11);


	m_pAnimator->CreateAnimation(L"MoveRightJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.08f, 11);
	m_pAnimator->CreateAnimation(L"MoveRightUpJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.08f, 11);
	m_pAnimator->CreateAnimation(L"MoveLeftJump", m_pJumpImage, Vector(700.f, 100.f), Vector(50.f, 50.f), Vector(-70.f, 0.f), 0.08f, 11);
	m_pAnimator->CreateAnimation(L"MoveLeftUpJump", m_pJumpImage, Vector(700.f, 100.f), Vector(50.f, 50.f), Vector(-70.f, 0.f), 0.08f, 11);

	m_pAnimator->CreateAnimation(L"MoveRightRunJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.08f, 11);
	m_pAnimator->CreateAnimation(L"MoveRightUpRunJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.08f, 11);
	m_pAnimator->CreateAnimation(L"MoveLeftRunJump", m_pJumpImage, Vector(700.f, 100.f), Vector(50.f, 50.f), Vector(-70.f, 0.f), 0.08f, 11);
	m_pAnimator->CreateAnimation(L"MoveLeftUpRunJump", m_pJumpImage, Vector(700.f, 100.f), Vector(50.f, 50.f), Vector(-70.f, 0.f), 0.08f, 11);


	m_pAnimator->CreateAnimation(L"IdleAttackJump", m_pAttackImage, Vector(0.f, 0.f), Vector(132.f, 132.f), Vector(150.f, 0.f), 0.02f, 35);
	m_pAnimator->CreateAnimation(L"IdleRightAttackJump", m_pAttackImage, Vector(0.f, 0.f), Vector(132.f, 132.f), Vector(150.f, 0.f), 0.02f, 35);
	m_pAnimator->CreateAnimation(L"IdleLeftAttackJump", m_pAttackImage, Vector(5070.f, 142.f), Vector(132.f, 132.f), Vector(-150.f, 0.f), 0.02f, 35);

	m_pAnimator->CreateAnimation(L"MoveRightAttackJump", m_pAttackImage, Vector(0.f, 0.f), Vector(132.f, 132.f), Vector(150.f, 0.f), 0.02f, 35);
	m_pAnimator->CreateAnimation(L"MoveLeftAttackJump", m_pAttackImage, Vector(5070.f, 142.f), Vector(132.f, 132.f), Vector(-150.f, 0.f), 0.02f, 35);
	m_pAnimator->CreateAnimation(L"MoveAttackJump", m_pAttackImage, Vector(0.f, 0.f), Vector(132.f, 132.f), Vector(150.f, 0.f), 0.02f, 35);


	m_pAnimator->Play(L"IdleRight", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(50, 55), Vector(0, 0));



}

void CLightKirby::Update()
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
		Logger::Debug(L"빛 공격이다");
		LigthAttack();
		
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

void CLightKirby::Render()
{
}

void CLightKirby::Release()
{
}




void CLightKirby::Gravity()
{
	if (m_Gravity == true)
		m_vecPos.y += m_fSpeed * DT * 2;
}



void CLightKirby::AnimatorUpdate()
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


void CLightKirby::LigthAttack()
{
	if (DownAttack == true)
	{
		LightKirbyShot* LightAttack = new LightKirbyShot;
		if (m_vecLookDir.x > 0)
			LightAttack->SetPos(m_vecPos.x + 30, GetPos().y);
		else if (m_vecLookDir.x < 0)
			LightAttack->SetPos(m_vecPos.x - 30, GetPos().y);

		LightAttack->SetDir(Vector(m_vecPos.x, m_vecMoveDir.y));
		ADDOBJECT(LightAttack);
	}
}

void CLightKirby::BasicKirby()
{

	Logger::Debug(L"커비가 능력을 뱉었다.");

	CGameObject* BasicKirby = new CPlayer;
	BasicKirby->SetPos(m_vecPos);
	ADDOBJECT(BasicKirby);

	CAMERA->SetTargetObj(BasicKirby);

	DELETEOBJECT(this);

}

void CLightKirby::OnCollisionEnter(CCollider* pOtherCollider)
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

void CLightKirby::OnCollisionStay(CCollider* pOtherCollider)
{

	if (pOtherCollider->GetObjName() == L"땅")
	{
		if (ontile >= 1)
			m_Gravity = false;
	}
}

void CLightKirby::OnCollisionExit(CCollider* pOtherCollider)
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
