#pragma once
#include "WinAPI.h"
class CGameManager : public SingleTon<CGameManager>
{
	friend SingleTon<CGameManager>;
	friend CCore;

public:
	CGameManager();
	virtual ~CGameManager();

private:
	void Init();
	void Update();
	void Release();
public:
	Vector PlayerPos;
};

#define GAME CGameManager::GetInstance()

