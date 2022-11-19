#pragma once
#include "CGameObject.h"

class CImage;
class CAnimator;
class CMonster;
class KirbyEat;
class CLightKirby;

enum class Playerstate { Idle, Run, Jump, Eat, Shot, Change, Takehit };


class CPlayer : public CGameObject
{
	friend KirbyEat;
	friend CMonster;
public:
	CPlayer();
	virtual ~CPlayer();

private:

	bool m_Basic;
	bool m_LightChange;
	bool m_Gravity;
	CAnimator* m_pAnimator;
	int m_pHp;

	bool Light;
	bool Ice;
	bool m_IceChange;
	
	

	CImage* m_pIdleImageR;
	CImage* m_pIdleImageRD;
	CImage* m_pIdleImageLD;
	CImage* m_pIdleImageU;
	CImage* m_pIdleImageL;
	CImage* m_pMoveImageR;
	CImage* m_pMoveImageL;
	CImage* m_pRunImageR;
	CImage* m_pRunImageL;
	CImage* m_pAttackImage;
	CImage* m_pAttackImageRD;
	CImage* m_pAttackImageLD;
	CImage* m_pChangeImage;
	CImage* m_pJumpImage;

	CLightKirby* LightKirby;

	Vector m_vecMoveDir;
	Vector m_vecLookDir;
	bool m_bIsMove;
	float m_fSpeed = 200.0f;

	int ontile;
protected:
	bool m_Eat;


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



	void Gravity();
	void Eat();
	void AnimatorUpdate();
	void Shot();
	void ChangePlayer();

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;
};

