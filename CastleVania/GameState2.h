#pragma once

#include "GameState.h"
#include "Items.h"
#include "Ground.h"
#include "Bat.h"
#include "Zombie.h"
#include "Panther.h"
#include "Global.h"
#include "mCandle.h"
#include "Merman.h"
#include "Stair.h"
#include "Ground_Null.h"
#include "Door.h"
#include "Grid.h"
#include "Boss.h"
#include "UI.h"
class GameState2 : public GameState
{
private:
	//Simon *simon
	DWORD timeStart;
	int time;
	bool isStart;
	bool isColisionDoor;
	bool isColisionDoor2;
	int count;
	bool isCheck;
	bool isCheck1;
	TileMap *tileMap;
	Items * item;
	mCandle* mcandle;
	D3DXVECTOR2 pos;
	Ground *ground;
	Stair * stair;
	Door *door;
	Door *door2;
	Ground0 * ground_null;

	Zombie *zombies[9];
	Panther *panther[3];
	Merman *merman[4];
	Bat *bats[2];
	Boss* boss;

	Grid *grid;

	

	vector<LPGAMEOBJECT> objects;
	vector<LPITEMS> listItem;
	//vector <LPENEMY*> listEnemy;

	//WaterAnimation *waterEffect[3];
	bool simonIsFallIntoWater;
public:
	GameState2();
	~GameState2();
	void Render();
	void Update(DWORD gameTime);
	void DestroyAll();

	void LoadResources();

	bool GetChangingState();
	void SetChangingState(bool status);
	bool CameraFollowHandle(float gameTime) { return true; }
	void Control();
};