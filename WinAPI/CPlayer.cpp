#include "framework.h"
#include "CPlayer.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CResourceManager.h"
#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"
#include "CMonster.h"

#include "CMissile.h"
#include "KirbyEat.h"
#include "KirbyShot.h"
#include "CLightKirby.h"
#include "CIceKirby.h"
#include "CGameManager.h"





CPlayer::CPlayer()
{
	ontile = 0;
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(100, 100);
	m_layer = Layer::Player;
	m_strName = L"플레이어";

	m_Eat = true;
	m_pIdleImageR = nullptr;
	m_pIdleImageU = nullptr;
	m_pIdleImageL = nullptr;
	m_pMoveImageR = nullptr;
	m_pMoveImageL = nullptr;
	m_pAttackImage = nullptr;

	m_vecMoveDir = Vector(0, 0);
	m_vecLookDir = Vector(0, -1);
	m_bIsMove = false;
	Jumpgo = false;
	JumpTime = 0.f;
	m_Basic = true;

	m_LightChange = false;
	LastJumpTime = 0.f;
	LastRunTime = 0;
	m_Gravity = true;
	m_pChangeImage = nullptr;
	LightKirby = nullptr;
	m_pRunImageR = nullptr;
	m_pRunImageL = nullptr;
	m_pIdleImageRD = nullptr;
	m_pIdleImageLD = nullptr;
	m_pAttackImageRD = nullptr;
	m_pAttackImageLD = nullptr;
	m_pJumpImage = nullptr;

	m_pHp = 10;
	Light = false;
	Ice = false;
	m_IceChange = false;

}


CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
	
	m_pAttackImage = RESOURCE->LoadImg(L"PlayerAttack", L"Image\\Kirby\\Basic\\KirbyEat.png");


	m_pChangeImage = RESOURCE->LoadImg(L"LightPlayerChange", L"Image\\Kirby\\Light\\LightKirbyChange.png");

	m_pAttackImageRD = RESOURCE->LoadImg(L"PlayerDownAttackR", L"Image\\Kirby\\Basic\\KirbyDownAttack.png");
	m_pIdleImageR = RESOURCE->LoadImg(L"PlayerIdleR", L"Image\\Kirby\\Basic\\KirbyIdleR.png");
	m_pIdleImageRD = RESOURCE->LoadImg(L"PlayerIdleRD", L"Image\\Kirby\\Basic\\KirbyDown.png");
	
	m_pIdleImageU = RESOURCE->LoadImg(L"PlayerIdleU", L"Image\\Kirby\\Basic\\KirbyFly.png");
	m_pIdleImageL = RESOURCE->LoadImg(L"PlayerIdleL", L"Image\\Kirby\\Basic\\KirbyIdleL.png");
	
	m_pMoveImageR = RESOURCE->LoadImg(L"PlayerMoveR", L"Image\\Kirby\\Basic\\KirbyRW.png");
	m_pMoveImageL = RESOURCE->LoadImg(L"PlayerMoveL", L"Image\\Kirby\\Basic\\KirbyLW.png");
	
	m_pJumpImage = RESOURCE->LoadImg(L"PlayerJump", L"Image\\Kirby\\Basic\\KirbyJump.png");

	m_pRunImageR  = RESOURCE->LoadImg(L"PlayerRunR", L"Image\\Kirby\\Basic\\KirbyRun.png");
	m_pRunImageL  = RESOURCE->LoadImg(L"PlayerRunL", L"Image\\Kirby\\Basic\\KirbyRun.png");

	// 캐릭터 45x43픽셀
	
	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"IdleUPDown", m_pChangeImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 10.0f, 1);

		m_pAnimator->CreateAnimation(L"IdleDownUP", m_pChangeImage, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"IdleUp", m_pIdleImageU, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 20);
		m_pAnimator->CreateAnimation(L"IdleRightUp", m_pIdleImageU, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 20);
		m_pAnimator->CreateAnimation(L"IdleRight", m_pIdleImageR, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"Idle", m_pIdleImageR, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"IdleRightDown", m_pIdleImageRD, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(43.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"IdleDown", m_pIdleImageRD, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(50.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"IdleLeft", m_pIdleImageL, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"IdleLeftDown", m_pIdleImageRD, Vector(0.f, 100.f), Vector(50.f, 50.f), Vector(50.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"IdleLeftUp", m_pIdleImageU, Vector(0.f, 100.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 20);


		m_pAnimator->CreateAnimation(L"IdleRightDownRun", m_pIdleImageRD, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(43.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"MoveRightDownRun", m_pIdleImageRD, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);
		m_pAnimator->CreateAnimation(L"MoveLeftDownRun", m_pIdleImageRD, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);
		m_pAnimator->CreateAnimation(L"IdleLeftDownRun", m_pIdleImageRD, Vector(0.f, 100.f), Vector(50.f, 50.f), Vector(50.f, 0.f), 10.0f, 1);


		m_pAnimator->CreateAnimation(L"MoveUp", m_pIdleImageU, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 20);
		m_pAnimator->CreateAnimation(L"MoveRight", m_pMoveImageR, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);
		m_pAnimator->CreateAnimation(L"MoveRightUp", m_pIdleImageU, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 20);
		m_pAnimator->CreateAnimation(L"MoveRightDown", m_pIdleImageRD, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);
		m_pAnimator->CreateAnimation(L"MoveLeftDown", m_pIdleImageRD, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);
		m_pAnimator->CreateAnimation(L"MoveLeft", m_pMoveImageL, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 10);
		m_pAnimator->CreateAnimation(L"MoveLeftUp", m_pIdleImageU, Vector(0.f, 100.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.08f, 20);

		m_pAnimator->CreateAnimation(L"IdleAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 9);
		m_pAnimator->CreateAnimation(L"IdleUpAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 9);
		m_pAnimator->CreateAnimation(L"IdleRightUpAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 9);
		m_pAnimator->CreateAnimation(L"IdleRightAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 9);
		m_pAnimator->CreateAnimation(L"IdleLeftUpAttack", m_pAttackImage, Vector(0.f, 100.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 9);
		m_pAnimator->CreateAnimation(L"IdleLeftAttack", m_pAttackImage, Vector(0.f, 100.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 9);
		m_pAnimator->CreateAnimation(L"IdleRightDownAttack", m_pAttackImageRD, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.5f, 2);
		m_pAnimator->CreateAnimation(L"IdleDownAttack", m_pAttackImageRD, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.5f, 2);
		m_pAnimator->CreateAnimation(L"IdleLeftDownAttack", m_pAttackImageRD, Vector(0.f, 100.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.5f, 2);

		m_pAnimator->CreateAnimation(L"MoveRightAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 9);
		m_pAnimator->CreateAnimation(L"MoveLeftAttack", m_pAttackImage, Vector(0.f, 100.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 9);
		m_pAnimator->CreateAnimation(L"MoveUpAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 9);
		m_pAnimator->CreateAnimation(L"MoveDownRightAttack", m_pAttackImageRD, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.5f, 2);
		m_pAnimator->CreateAnimation(L"MoveDownLeftAttack", m_pAttackImageRD, Vector(0.f, 100.f), Vector(50.f, 50.f), Vector(70.f, 0.f), 0.5f, 2);
		m_pAnimator->CreateAnimation(L"MoveAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 9);

		
		m_pAnimator->CreateAnimation(L"IdleRun", m_pRunImageR, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 8);
		m_pAnimator->CreateAnimation(L"IdleRightRun", m_pRunImageR, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 8);
		m_pAnimator->CreateAnimation(L"IdleLeftRun", m_pRunImageR, Vector(490.f, 104.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.05f, 8);

		m_pAnimator->CreateAnimation(L"MoveUpRun", m_pRunImageR, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 8);
		m_pAnimator->CreateAnimation(L"MoveRightRun", m_pRunImageR, Vector(0.f, 0.f), Vector(60.f, 50.f), Vector(70.f, 0.f), 0.05f, 8);
		m_pAnimator->CreateAnimation(L"MoveLeftRun", m_pRunImageR, Vector(490.f, 104.f), Vector(60.f, 50.f), Vector(-70.f, 0.f), 0.05f, 8);


		m_pAnimator->CreateAnimation(L"MoveRightAttackRun", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 9);
		m_pAnimator->CreateAnimation(L"MoveLeftAttackRun", m_pAttackImage, Vector(0.f, 100.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 9);
		m_pAnimator->CreateAnimation(L"MoveUpAttackRun", m_pAttackImage, Vector(0.f, 0.f), Vector(59.f, 59.f), Vector(69.f, 0.f), 0.09f, 9);


		m_pAnimator->CreateAnimation(L"IdleJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9);
		m_pAnimator->CreateAnimation(L"IdleRightJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9);
		m_pAnimator->CreateAnimation(L"IdleLeftJump", m_pJumpImage, Vector(0.f, 90.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9);

		m_pAnimator->CreateAnimation(L"MoveRightJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9);
		m_pAnimator->CreateAnimation(L"MoveRightUpJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9);
		m_pAnimator->CreateAnimation(L"MoveLeftJump", m_pJumpImage, Vector(0.f, 90.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9);
		m_pAnimator->CreateAnimation(L"MoveLeftUpJump", m_pJumpImage, Vector(0.f, 90.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9);
	
		m_pAnimator->CreateAnimation(L"MoveRightRunJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9);
		m_pAnimator->CreateAnimation(L"MoveRightUpRunJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9);
		m_pAnimator->CreateAnimation(L"MoveLeftRunJump", m_pJumpImage, Vector(0.f, 90.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9);
		m_pAnimator->CreateAnimation(L"MoveLeftUpRunJump", m_pJumpImage, Vector(0.f, 90.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9);

		m_pAnimator->CreateAnimation(L"IdleRunJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9);
		m_pAnimator->CreateAnimation(L"IdleRightRunJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9);
		m_pAnimator->CreateAnimation(L"IdleRightUpRunJump", m_pJumpImage, Vector(0.f, 0.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9);
		m_pAnimator->CreateAnimation(L"IdleLeftRunJump", m_pJumpImage, Vector(0.f, 90.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9);
		m_pAnimator->CreateAnimation(L"IdleLeftUpRunJump", m_pJumpImage, Vector(0.f, 90.f), Vector(50.f, 50.f), Vector(58.f, 0.f), 0.08f, 9);


		m_pAnimator->CreateAnimation(L"IdleAttackJump", m_pAttackImage, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 0.03f, 1);
		m_pAnimator->CreateAnimation(L"IdleRightAttackJump", m_pAttackImage, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 0.03f, 1);
		m_pAnimator->CreateAnimation(L"IdleLeftAttackJump", m_pAttackImage, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 10.0f, 1);

		m_pAnimator->CreateAnimation(L"MoveRightAttackJump", m_pAttackImage, Vector(0.f, 0.f), Vector(10.f, 10.f), Vector(45.f, 0.f), 10.0f, 3);
		m_pAnimator->CreateAnimation(L"MoveLeftAttackJump", m_pAttackImage, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 10.0f, 1);
		m_pAnimator->CreateAnimation(L"MoveAttackJump", m_pAttackImage, Vector(0.f, 0.f), Vector(45.f, 43.f), Vector(45.f, 0.f), 10.0f, 1);

	m_pAnimator->Play(L"IdleUp", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(45, 45), Vector(0, 0));
}

void CPlayer::Update()
{
	Gravity();
	m_bIsMove = false;
	/*
	======리소스 명단=====
	1. 일반 커비	== [완료] ==> 리소스 행동조건만 걸면 됌 먹기 뱉기 흡수 적용하면 됌
	3. 몬스터	[일반] == [완료] 
	4. 특별 몬스터 [빛, 얼음] == [완료]
	5. 보스   ==[두두] [완성]
	5.5 빛 커비 & 얼음커비 [완성] 
	=====몬스터 코드 추가 필요=====
	===플레이어 코드 추가 필요======
	6. 맵 수정 & 보스맵 만들기 
	7. 상호작용 [문] == 오브젝트 생성
	8. UI [체력바 변신상태]  == 체력바가 없는데 실벌탱
	=====================
	


	======보류 명단=======
	 1. 달리기 구현
	 ㄴ 왼쪽	 [-> + ->]
	 ㄴ 오른쪽  [<- + <-]

	 2. 먹기 오류 [최대한 빨리 해야할듯] 
	 ㄴ 플레이어가 닿는 판정을 어떤걸로 바꿔야함 == eat에 엔터했을때 0.5후에 사라지게 하면 될듯?
	
	 3. 벽과 땅 타일 구분 == 밑, 위 왼쪽에서 충돌시 챔피언 위치 x+ 되는거 해결 바람

	 4. 몬스터 평상시였다가 죽는 모션 추가해야함

	 5. 플레이어 공격 오브젝트가 도망감 ㅋㅋ

	 6. 킹 데미지 들어가면 이미지 바꾸기 && 몬스터포함 움직임 구현 왔다갔따 킹은 점프 구현 시간으로 하면 될 듯
		ㄴ 온콜리전 엔터하면 ==> 변수 만들어서 타임 받고 그시간동안 데미지받은 이미지 출력 하면 될수도
	
	 7. 보스방 입장시 전에 가지고 있던 능력 그대로 복사해서 가져가야함 이건 진짜 생각이 안남

	===플레이어 코드 추가 필요====== > 특정행동시에 못하게끔?
 	======================
	
	
	======해야 할 명단=======
	 11. 보스스테이지 넘어갈때 게임매니저에서 가져갈까?
	 12. 보스 죽이면 영상
	 13. 내가 죽으면 어캄?
	 14. 보류 
	========================
	ㄴ
	=======진행중========
	 8. 보스맵 & 맵 수정크기
	 9. UI 만들기 == 체력바 깎이는 거 ㄱ
 	 11. 타이틀화면
	=====================



	======완성 명단=======
	 1. 뒷 배경 , 맵 타일 사이즈 맞게 수정 요망 줄이면 될듯 조금만 32배수로
	 2. 일반 몬스터 구현
	 3. 특수몬스터 구현 
	 4. 흡수 기능 완성
	 5. 변신 기능 완성
	 6. 변신 벗기 기능 완성
	 7. 몬스터 구현 완성 [보스 일반 특별]
	 8. 상호작용[문 == 특정버튼시 보스방]
	 9. 얼음커비 완성 
	=====================
	*/

	GAME->PlayerPos = m_vecPos;

	if (m_pHp <= 0)
	{
		DELETEOBJECT(this);
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
		else if (BUTTONSTAY(VK_DOWN)/*LastRunTime <= 0.15f && BUTTONSTAY(VK_LEFT)*/)
		{
			m_vecMoveDir.x = -1;
			m_bIsMove = false;
		}
		else if (BUTTONSTAY('R') && BUTTONSTAY(VK_DOWN)/*LastRunTime <= 0.15f && BUTTONSTAY(VK_LEFT)*/)
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
		LastRunTime += DT;
		if(BUTTONSTAY('R') /*&& LastRunTime <= 0.15f && BUTTONSTAY(VK_RIGHT)*/)
		{ 
			m_vecPos.x += m_fSpeed * DT *2.f;
			m_bIsMove = true;
			m_vecMoveDir.x = +1;
			LastRunTime = 0;
		}
		else if (BUTTONSTAY('S'))
		{
			m_vecMoveDir.x = 0;
			m_bIsMove = false;
		}

		else if (BUTTONSTAY(VK_DOWN)/*LastRunTime <= 0.15f && BUTTONSTAY(VK_LEFT)*/)
		{
			m_vecMoveDir.x = +1;
			m_bIsMove = false;
		}

		else if (BUTTONSTAY(VK_DOWN) && BUTTONSTAY('R'))/*LastRunTime <= 0.15f && BUTTONSTAY(VK_LEFT)*/
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

	else
	{
		m_vecMoveDir.x = 0;
	}

	if (m_Eat == false && BUTTONDOWN(VK_DOWN))
	{
		Logger::Debug(L"커비가 소화시켰다");
		m_Eat = true;

		if (m_LightChange == true)
		{
			Logger::Debug(L"커비가 빛으로 변신했다");
			m_Basic = false;
			ChangePlayer();
		}
		else if (m_IceChange == true)
		{
			Logger::Debug(L"커비가 얼음으로 변신했다");
			m_Basic = false;
			ChangePlayer();
		}
	}

	if (BUTTONSTAY(VK_DOWN) && BUTTONDOWN('S'))
	{

		m_vecPos.x += m_fSpeed * DT +100; 
		// 시간 넣어서 그 시간만큼 이 거리를 이동하게 끔 설정
	}

	if (BUTTONDOWN('S'))
	{
		if (m_Basic == true)
		{
			if (m_Eat)  //true
			{
				Eat();
			}
			else // false
			{
				Shot();
			}
		}

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
				m_vecPos.y -= m_fSpeed * DT * 3;
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


void CPlayer::Gravity()
{
	if (m_Gravity == true)
		m_vecPos.y += m_fSpeed * DT * 2;
	

}
	
void CPlayer::Render()
{
}

void CPlayer::Release()
{
	
}


void CPlayer::AnimatorUpdate()
{

	wstring str = L"";

	if (m_vecMoveDir.Length() > 0)
		m_vecLookDir = m_vecMoveDir;

	if (m_bIsMove)	str += L"Move";
	else			str += L"Idle";

	if (m_vecLookDir.x > 0) str += L"Right";
	else if (m_vecLookDir.x < 0) str += L"Left";

	if (BUTTONSTAY(VK_UP)) str += L"Up";
	if (BUTTONSTAY(VK_DOWN)) str += L"Down";


	if (BUTTONSTAY('S')) str += L"Attack";

	if (BUTTONSTAY('R')) str += L"Run";

	if (BUTTONSTAY('A')) str += L"Jump";



	m_pAnimator->Play(str, false);
}

void CPlayer::Shot()
{
	Logger::Debug(L"Shot");
	KirbyShot* Shot = new KirbyShot;
	Shot->SetPos(m_vecPos);
	Shot->SetDir(Vector(m_vecLookDir.x, m_vecMoveDir.y));
	ADDOBJECT(Shot);
	m_Eat = true;
  
}

void CPlayer::ChangePlayer()
{
	if (Light == true)
	{
		CGameObject* lightKirby = new CLightKirby();
		lightKirby->SetPos(m_vecPos);
		ADDOBJECT(lightKirby);
		
		DELETEOBJECT(this);
	}
	else if (Ice == true)
	{
		CGameObject* IceKirby = new CIceKirby();
		IceKirby->SetPos(m_vecPos);
		ADDOBJECT(IceKirby);
		
		DELETEOBJECT(this);
	}
}

void CPlayer::Eat()
{
	Logger::Debug(L"공격오브젝트 생성");

	KirbyEat* m_KE = new KirbyEat;
	if (m_vecLookDir.x > 0)
		m_KE->SetPos(m_vecPos.x + 30, GetPos().y);
	else if (m_vecLookDir.x < 0)
		m_KE->SetPos(m_vecPos.x - 30, GetPos().y);

	m_KE->SetDir(Vector(m_vecPos.x, m_vecMoveDir.y));
	if (BUTTONSTAY(VK_DOWN))
		DELETEOBJECT(m_KE);
	else
	ADDOBJECT(m_KE);
	// 다른 클래스의 온콜리전익싯을 가져올수있나
}



void CPlayer::OnCollisionEnter(CCollider* pOtherCollider)
{
	
	if (pOtherCollider->GetObjName() == L"몬스터")
	{
		Logger::Debug(L"몬스터와 부딪혀 데미지를 입습니다.");
		m_LightChange = false;
		m_IceChange = false;
		m_Eat = false;
		m_pHp -= 1;
		Light = false;
		Ice = false;
		CGameObject* pl = pOtherCollider->GetOwner();
		if (pl->GetPos().x <= m_vecPos.x)
			m_vecPos.x += 20;
		else if (pl->GetPos().x >= m_vecPos.x)
			m_vecPos.x -= 20;
	}
	if (pOtherCollider->GetObjName() == L"얼음 몬스터")
	{
		Logger::Debug(L"몬스터와 부딪혀 데미지를 입습니다.");
		Light = false;
		m_IceChange = true;
		Ice = true;
		m_LightChange = false;
		m_Eat = false;
		m_pHp -= 1;
		CGameObject* pl = pOtherCollider->GetOwner();
		if (pl->GetPos().x <= m_vecPos.x)
			m_vecPos.x += 20;
		else if (pl->GetPos().x >= m_vecPos.x)
			m_vecPos.x -= 20;
	}


	if (pOtherCollider->GetObjName() == L"빛몬스터")
	{
		Logger::Debug(L"몬스터와 부딪혀 데미지를 입습니다.");
		Ice = false;
		Light = true;
		m_LightChange = true;
		m_Eat = false;
		m_pHp -= 1;
		m_IceChange = false;

		CGameObject* pl = pOtherCollider->GetOwner();
		if (pl->GetPos().x <= m_vecPos.x)
			m_vecPos.x += 20;
		else if (pl->GetPos().x >= m_vecPos.x)
			m_vecPos.x -= 20;


	}
	
	if (pOtherCollider->GetObjName() == L"먹기")
	{
		Logger::Debug(L"몬스터를 삼켰다?");
		CGameObject* Eat = pOtherCollider->GetOwner();
		
	}

	if (pOtherCollider->GetObjName() == L"땅")
	{
		if(ontile >= 1)
		m_Gravity = false;
		++ontile;
	}

	if (pOtherCollider->GetObjName() == L"보스 몬스터")
	{
		Logger::Debug(L"몬스터와 부딪혀 데미지를 입습니다.");
		m_LightChange = false;
		m_pHp -= 1;
		Light = false;
		m_IceChange = false;
		Ice = false;
		CGameObject* pl = pOtherCollider->GetOwner();
		if (pl->GetPos().x <= m_vecPos.x)
			m_vecPos.x += 20;
		else if (pl->GetPos().x >= m_vecPos.x)
			m_vecPos.x -= 20;

	}
}




void CPlayer::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"땅")
	{	
		if (ontile >= 1)
		m_Gravity = false;
	}
}

void CPlayer::OnCollisionExit(CCollider* pOtherCollider)
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



