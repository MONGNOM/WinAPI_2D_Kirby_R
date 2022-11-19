#include "framework.h"
#include "CGroundTile.h"

#include "CResourceManager.h"
#include "CRenderManager.h"
#include "CCollider.h"

CGroundTile::CGroundTile()
{
	m_strName  = L"땅";
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
	// 땅타일과 충돌했을 경우 처리
	if (pOther->GetObjName() == L"플레이어")
	{
		Logger::Debug(L"땅과 접촉했다.");
	}
	if (pOther->GetObjName() == L"땅")
	{
		/*Logger::Debug(L"땅을 밟고 있다.");*/
	}
}

void CGroundTile::OnCollisionStay(CCollider* pOther)
{
	// 땅타일과 충돌했을 경우 처리
	if (pOther->GetObjName() == L"땅")
	{
		/*Logger::Debug(L"땅을 밟고 있다.");*/
	
	}
	
}

void CGroundTile::OnCollisionExit(CCollider* pOther)
{
	if (pOther->GetObjName() == L"플레이어")
	{
		Logger::Debug(L"땅과 떨어졌다.");
	}

}
