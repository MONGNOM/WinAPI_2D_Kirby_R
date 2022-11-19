#pragma once
#include "CGameObject.h"

class CSceneStage01;

class CDoor : public CGameObject
{
	CDoor();
	virtual ~CDoor();


	friend CSceneStage01;

private:
	bool DoorOpen;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	
	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;

};

