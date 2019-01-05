#pragma once
#include "GameState.h"
#include "Sprites.h"
#include "BatIntro.h"
#include "Helicop.h"
#include "Global.h"
#include "Ground_Null.h"
class GameIntro : public GameState
{
private:

	float timeDelay;
	TileMap *tileMap;
	D3DXVECTOR2 pos;
	Helicop *helicopter;

	Ground0 *ground;
	vector<LPGAMEOBJECT> objects;
	BatIntro *bat[2];

public:


	GameIntro();
	~GameIntro();
	void LoadResources();
	void Render();
	void Update(DWORD gameTime);
	void DestroyAll();
	bool GetChangingState() { return GameState::GetChangingState(); }
	void SetChangingState(bool status) { GameState::SetChangingState(status); }
	bool CameraFollowHandle(float gameTime) { return true; }
};