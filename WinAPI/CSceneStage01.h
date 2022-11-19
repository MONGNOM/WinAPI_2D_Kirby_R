#pragma once
#include "CScene.h"

class CPlayer;
class CLightKirby;
class CDoor;

class CSceneStage01 : public CScene
{

	friend CPlayer;
	friend CLightKirby;
	friend CDoor;


public:
	CSceneStage01();
	virtual ~CSceneStage01();

private:
	CPlayer* pPlayer;
	CLightKirby* LPlayer;
	bool m_LightChange;
	bool m_Basic;



private:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;
};
