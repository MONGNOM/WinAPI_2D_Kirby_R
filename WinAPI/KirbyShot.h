#pragma once
#include "CGameObject.h"
class KirbyShot : public CGameObject
{
public:
	KirbyShot();
	virtual ~KirbyShot();

private:
	Vector m_vecDir;
	float m_fVelocity;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionEnter(CCollider * pOtherCollider) override;

public:
	void SetDir(Vector dir);
	void SetVelocity(float velocity);
};

