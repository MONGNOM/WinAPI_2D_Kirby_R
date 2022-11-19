#include "framework.h"
#include "CGroundTile.h"

#include "CResourceManager.h"
#include "CRenderManager.h"
#include "CCollider.h"

CGroundTile::CGroundTile()
{
	m_strName  = L"��";
	m_type = TypeTile::Ground;
	m_layer = Layer::Tile;
}

CGroundTile::~CGroundTile()
{
}

void CGroundTile::Init()
{
	CTile::Init();

	AddCollider(ColliderType::Rect,
		Vector(CTile::TILESIZE, CTile::TILESIZE),
		Vector(CTile::TILESIZE / 2, CTile::TILESIZE / 2));
}

void CGroundTile::Update()
{
	CTile::Update();
}

void CGroundTile::Render()
{
	CTile::Render();

	ComponentRender();
}

void CGroundTile::Release()
{
	CTile::Release();
}

void CGroundTile::OnCollisionEnter(CCollider* pOther)
{
	// ��Ÿ�ϰ� �浹���� ��� ó��
	if (pOther->GetObjName() == L"�÷��̾�")
	{
		Logger::Debug(L"���� �����ߴ�.");
	}
	if (pOther->GetObjName() == L"��")
	{
		/*Logger::Debug(L"���� ��� �ִ�.");*/
	}
}

void CGroundTile::OnCollisionStay(CCollider* pOther)
{
	// ��Ÿ�ϰ� �浹���� ��� ó��
	if (pOther->GetObjName() == L"��")
	{
		/*Logger::Debug(L"���� ��� �ִ�.");*/
	
	}
	
}

void CGroundTile::OnCollisionExit(CCollider* pOther)
{
	if (pOther->GetObjName() == L"�÷��̾�")
	{
		Logger::Debug(L"���� ��������.");
	}

}
