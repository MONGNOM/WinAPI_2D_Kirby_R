#pragma once
#include "CGameObject.h"
#include "CPlayer.h"

class CImage;
class CAnimator;
class CMonster;
class KirbyEat;
class CSceneStage01;

class CIceKirby : public CGameObject
{
	friend KirbyEat;
	friend CPlayer;
	friend CMonster;
	friend CSceneStage01;
public:
	CIceKirby();
	virtual ~CIceKirby();

private:

protected:
	bool m_Eat;
	int m_pHp;
	bool DownAttack;
	bool m_Basic;
	bool m_LightChange;
	bool m_Gravity;
	CAnimator* m_pAnimator;

	CImage* m_pIdleImageR;
	CImage* m_pIdleImageRD;
	CImage* m_pIdleImageLD;
	CImage* m_pIdleImageU;
	CImage* m_pIdleImageL;
	CImage* m_pMoveImage;
	CImage* m_pRunImageR;
	CImage* m_pRunImageL;
	CImage* m_pAttackImage;
	CImage* m_pAttackImageRD;
	CImage* m_pAttackImageLD;
	CImage* m_pChangeImage;
	CImage* m_pJumpImage;

	Vector m_vecMoveDir;
	Vector m_vecLookDir;
	bool m_bIsMove;
	float m_fSpeed = 200.0f;

	int ontile;

	float JumpTime;
	bool Jumpgo;
	float LastJumpTime;
	float LastRunTime;
	float GravityJumpTime;


private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;


	void BasicKirby();
	void Gravity();
	void AnimatorUpdate();
	void IceAttack();

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;
};

