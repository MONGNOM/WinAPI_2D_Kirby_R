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

	// 화면밖으로 나갈경우 삭제
	
	// ㄴ 벽에 붙이칠 때로 변경 예정 && 어느정도 화면 밖으로 나가면 삭제 포함 //
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
	Logger::Debug(L"미사일이 충돌체와 부딪혀 사라집니다.");
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
