#pragma once

class CPlayer;

class CPlayerState
{
	friend CPlayer;
private :

	CPlayer* pPlayer;

public :
	CPlayerState();
	virtual ~CPlayerState();

	virtual void Init() =0;
	virtual void Update() =0;
	virtual void Render() =0;
	virtual void Release() =0;


};

