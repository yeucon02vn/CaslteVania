#pragma once
#include "GameState.h"
#include "Ground.h"
#include "lCandle.h"
#include "Items.h"
#include "UI.h"

class GameState1 : public GameState
{
private:
	TileMap *tileMap; 
	float timeDelay;
	D3DXVECTOR2 pos;
	lCandle *lcandle;
	Items * item;
	Ground* ground;
	vector<LPGAMEOBJECT> objects;
	vector<LPITEMS> listItem;
	bool NoControl;
public:
	GameState1();
	~GameState1();
	void Render();
	void Update(DWORD gameTime);
	void DestroyAll();

	void LoadResources();

	bool GetChangingState();
	void SetChangingState(bool status);
	bool CameraFollowHandle(float gameTime) { return true; }
	void Control();
	

};

