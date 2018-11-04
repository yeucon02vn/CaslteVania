#pragma once
#pragma once
#include "GameState.h"
#include "TileMap.h"
#include "Simon.h"
#include "QuadTree.h"
#include "Ground.h"
#include "Candle.h"
#include "Sprite.h"


class GamePlayStateOne : public GameState
{
private:
	Simon *simon;
	TileMap *tileMap;

	Sprite *sprite;
	Sprite	*castleSprite;

	GameObject *ground;
	GameObject *cameraObject;
	GameObject *leftCamera;
	GameObject *rightCamera;

	QuadTree *quadTree;

	std::vector<GameObject*> *list;
	LPDIRECT3DDEVICE9 gDevice;

public:
	GamePlayStateOne();
	~GamePlayStateOne();
	bool Initialize(Graphics *graphics);
	void Render();
	void Update(float gameTime);
	void DestroyAll();
	/*
	* Overload tu class cha
	* Set va get gia tri cua $changeState
	*/
	bool GetChangingState();
	void SetChangingState(bool status);
	bool CameraFollowHandle(float gameTime) { return true; }
};

