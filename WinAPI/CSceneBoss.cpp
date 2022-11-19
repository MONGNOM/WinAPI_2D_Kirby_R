#include "framework.h"
#include "CSceneBoss.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CButton.h"
#include "CPanel.h"
#include "CGround.h"
#include "CBackGround.h"
#include "CLightMonster.h"
#include "CLightKirby.h"
#include "CIceMonster.h"
#include "CKIngMonster.h"


CSceneBoss::CSceneBoss()
{
	pPlayer = nullptr;
	LPlayer = nullptr;
}

CSceneBoss::~CSceneBoss()
{
}

void CSceneBoss::Init()
{
}

void CSceneBoss::Enter()
{

	CMonster* pMonster = new CMonster();
	pMonster->SetPos(700, 300);
	AddGameObject(pMonster);

	CLightMonster* pMonster1 = new CLightMonster();
	pMonster1->SetPos(450, 300);
	AddGameObject(pMonster1);

	CIceMonster* pMonster12 = new CIceMonster();
	pMonster12->SetPos(900, 300);
	AddGameObject(pMonster12);

	CKIngMonster* pMonster123 = new CKIngMonster();
	pMonster123->SetPos(1200, 300);
	AddGameObject(pMonster123);

	CGround* Ground = new CGround;
	Ground->SetImage(RESOURCE->LoadImg(L"BackGround", L"Image\\Ground.png"));
	AddGameObject(Ground);

	CBackGround* BackGround = new CBackGround;
	BackGround->SetImage(RESOURCE->LoadImg(L"BbackGround", L"Image\\BackGround_1.png"));
	AddGameObject(BackGround);

	pPlayer = new CPlayer();
	pPlayer->SetPos(250, 500);
	ADDOBJECT(pPlayer);

	CAMERA->SetTargetObj(pPlayer);

	CAMERA->FadeIn(0.25f);
	LoadTile(GETPATH + L"Tile\\Boss.tile");

}

void CSceneBoss::Update()
{

	if (BUTTONDOWN(VK_ESCAPE))
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Title, 0.25f);
	}
}

void CSceneBoss::Render()
{
}

void CSceneBoss::Exit()
{
	DeleteAll();

}

void CSceneBoss::Release()
{
}
