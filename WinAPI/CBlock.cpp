#include "framework.h"
#include "CBlock.h"

#include "CResourceManager.h"
#include "CRenderManager.h"
#include "CCollider.h"
#include "CTile.h"
#include "CPlayer.h"

CBlock::CBlock()
{
	m_strName = L"벽";
	m_type = TypeTile::Wall;
	m_layer = Layer::Tile;
	
}

CBlock::~CBlock()
{
}

void CBlock::Init()
{
	CTile::Init();

	AddCollider(ColliderType::Rect,
		Vector(CTile::TILESIZE, CTile::TILESIZE),
		Vector(CTile::TILESIZE / 2, CTile::TILESIZE / 2));
}

void CBlock::Update()
{
	CTile::Update();
}

void CBlock::Render()
{
	CTile::Render();

	ComponentRender();
}

void CBlock::Release()
{
	CTile::Release();

}

void CBlock::OnCollisionEnter(CCollider* pOther)
{
	if (pOther->GetObjName() == L"플레이어")
	{

		Logger::Debug(L"플레이어가 벽에 부딪혀 밀려납니다");
	
		//조건 왼쪽이면 충돌시 왼쪽으로 밀기 && 반대방향도 마찬가지
		CGameObject* pl = pOther->GetOwner();
		if (GetTilePosX() >= GAME->PlayerPos.x)
			pl->SetPos(GAME->PlayerPos.x += 5, pl->GetPos().y);
		else
			pl->SetPos(GAME->PlayerPos.x -= 5, pl->GetPos().y);

		 
	}
}

void CBlock::OnCollisionStay(CCollider* pOther)
{
	if (pOther->GetObjName() == L"플레이어")
	{

		Logger::Debug(L"플레이어가 벽에 부딪혀 밀려납니다");

		//조건 왼쪽이면 충돌시 왼쪽으로 밀기 && 반대방향도 마찬가지
		CGameObject* pl = pOther->GetOwner();
		if (GetTilePosX() <= GAME->PlayerPos.x)
			pl->SetPos(GAME->PlayerPos.x += 5, pl->GetPos().y);
		else
			pl->SetPos(GAME->PlayerPos.x -= 5, pl->GetPos().y);


	}
}

void CBlock::OnCollisionExit(CCollider* pOther)
{
	
}
