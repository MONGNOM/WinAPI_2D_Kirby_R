#pragma once
class KirbyStatus
{
	KirbyStatus();
	virtual ~KirbyStatus();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

	// Idle, walk, run, jump, eat, shot, change,

};

class KirbyIdle : KirbyStatus
{
	KirbyIdle();
		virtual ~KirbyIdle();


};

