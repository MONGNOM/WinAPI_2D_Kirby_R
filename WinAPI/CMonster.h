#pragma once
#include "CGameObject.h"

class CPlayer;
class CAnimator;


class CMonster : public CGameObject
{
	friend CPlayer;
public:
	CMonster();
	virtual ~CMonster();

	void SetDir(Vector dir);
	void SetVelocity(float velocity);

private:
	wstring str = L"";
	bool m_Gravity = true;
	Vector m_vecDir;
	float m_fVelocity;
	float m_fSpeed = 200.0f;
	CImage* m_mMoveImage;
	CImage* m_mDieImage;
	CAnimator* m_pAnimator;
	bool slide;
	float slideTime;
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
	bool HP;
	float DieTime;
	
	void AnimatorUpdate();
protected:
	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;
};

