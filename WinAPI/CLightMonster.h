#pragma once
#include "CGameObject.h"


class CPlayer;

class CLightMonster : public CGameObject
{
	friend CPlayer;
public:
	CLightMonster();
	virtual ~CLightMonster();

	void SetDir(Vector dir);
	void SetVelocity(float velocity);

private:

	bool m_Gravity = true;
	Vector m_vecDir;
	float m_fVelocity;
	float m_fSpeed = 200.0f;
	CImage* m_mMoveImage;
	CImage* m_mDieImage;
	CImage* m_mAttackImage;
	CAnimator* m_pAnimator;

	int m_mHp;
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	void Gravity();
	
	Vector m_vecMoveDir;
	Vector m_vecLookDir;
	bool m_bIsMove;
	bool Iscrash;
	float DieTime;
	bool slide;
	float slideTime;
	void AnimatorUpdate();

protected:
	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;
};

