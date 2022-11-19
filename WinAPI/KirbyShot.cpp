#include "framework.h"
#include "KirbyShot.h"


#include "CRenderManager.h"
#include "CTimeManager.h"
#include "CEventManager.h"
#include "CCollider.h"

KirbyShot::KirbyShot()
{
	m_vecScale = Vector(10, 10);
	m_vecDir = Vector(0, 0);
	m_fVelocity = 700;
	m_layer = Layer::Shot;
	m_strName = L"Shot";
}

KirbyShot::~KirbyShot()
{
}

void KirbyShot::Init()
{
	AddCollider(ColliderType::Rect, Vector(20, 20), Vector(0, 0));
}

void KirbyShot::Update()
{
	m_vecPos += m_vecDir * m_fVelocity * DT;

	// ȭ������� ������� ����
	
	// �� ���� ����ĥ ���� ���� ���� && ������� ȭ�� ������ ������ ���� ���� //
	if (m_vecPos.x < 0 ||
		m_vecPos.x > WINSIZEX ||
		m_vecPos.y < 0 ||
		m_vecPos.y > WINSIZEY);
		/*DELETEOBJECT(this);*/


}

void KirbyShot::Render()
{
	RENDER->FrameCircle(
		m_vecPos.x,
		m_vecPos.y,
		m_vecScale.x);
}

void KirbyShot::Release()
{
}

void KirbyShot::OnCollisionEnter(CCollider* pOtherCollider)
{
	Logger::Debug(L"�̻����� �浹ü�� �ε��� ������ϴ�.");
	DELETEOBJECT(this);
	
}

void KirbyShot::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}

void KirbyShot::SetVelocity(float velocity)
{
	m_fVelocity = velocity;
}
