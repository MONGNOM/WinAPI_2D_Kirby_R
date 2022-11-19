#pragma once
#include "CScene.h"

class CPlayer;
class CLightKirby;

class CSceneBoss : public CScene
{

	friend CPlayer;
	friend CLightKirby;

public:
	CSceneBoss();
	virtual ~CSceneBoss();

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

