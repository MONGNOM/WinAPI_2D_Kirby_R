#pragma once
#include "CGameObject.h"

class CPlayer;

class KirbyEat : public CGameObject
{

	friend CPlayer;
public:
	KirbyEat();
	virtual~KirbyEat();

private:

	Vector m_vecDir;
	Vector m_vecMoveDir;
	Vector m_vecLookDir;
	CAnimator* m_pAnimator;

	CImage* m_pIdleImage;
	CImage* m_pMoveImage;
	bool m_bIsMove;

	void AnimatorUpdate();
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

public:
	void SetDir(Vector dir);

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;
};

