#include "framework.h"
#include "CSceneStage01.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"
#include "CPathManager.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CCameraController.h"
#include "CButton.h"
#include "CPanel.h"
#include "CImageObject.h"
#include "CGround.h"
#include "CBackGround.h"
#include "CLightMonster.h"
#include "CLightKirby.h"
#include "CIceMonster.h"
#include "CKIngMonster.h"
#include "CDoor.h"

CSceneStage01::CSceneStage01()
{
	pPlayer = nullptr;
	LPlayer = nullptr;
	m_Basic = true;

}

CSceneStage01::~CSceneStage01()
{
}



void CSceneStage01::Init()
{
	
}

void CSceneStage01::Enter()
{

	CMonster* pMonster = new CMonster();
	pMonster->SetPos(2000, 400);
	AddGameObject(pMonster);

	CLightMonster* pMonster1 = new CLightMonster();
	pMonster1->SetPos(500, 400);
	AddGameObject(pMonster1);

	CIceMonster* pMonster12 = new CIceMonster();
	pMonster12->SetPos(900, 400);
	AddGameObject(pMonster12);

	CDoor* Door = new CDoor();
	Door->SetPos(4930, 440);
	AddGameObject(Door);




	CCameraController* pCamController = new CCameraController;
	AddGameObject(pCamController);

	CGround* Ground = new CGround;
	Ground->SetImage(RESOURCE->LoadImg(L"BackGround", L"Image\\Ground.png"));
	AddGameObject(Ground);

	CBackGround* BackGround = new CBackGround;
	BackGround->SetImage(RESOURCE->LoadImg(L"BbackGround", L"Image\\BackGround_1.png"));
	AddGameObject(BackGround);

	pPlayer = new CPlayer();
	pPlayer->SetPos(300, 500);
	ADDOBJECT(pPlayer);

	CAMERA->SetTargetPos(Vector(400, 500));
	

	CAMERA->FadeIn(0.25f);
	LoadTile(GETPATH + L"Tile\\Stage01.tile");


}

void CSceneStage01::Update()
{

	if (GAME->PlayerPos.x >= 4658)
	{
		CAMERA->SetTargetPos(Vector(4658, GAME->PlayerPos.y),0.1f);
	}
	else if (GAME->PlayerPos.x <= 400)
	{
		CAMERA->SetTargetPos(Vector(400, GAME->PlayerPos.y),0.1f);

	}
	else
		CAMERA->SetTargetPos(GAME->PlayerPos,0.1f);


	


	if (BUTTONDOWN(VK_ESCAPE))
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Title, 0.25f);
	}

}

void CSceneStage01::Render()
{
	
}

void CSceneStage01::Exit()
{
	DeleteAll();
}

void CSceneStage01::Release()
{
}
