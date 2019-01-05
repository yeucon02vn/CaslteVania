
#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__
#include <fstream>
#include <vector>
#include "Items.h"
#include "Simon.h"
#include "Game.h"
#include "TileMap.h"
#include "UI.h"

static int score;



class GameState
{
	float simonDeadTime = 1.5;
protected:
	bool changeState;
	float time;

	bool canUseKeyboard;
	static Simon* simon;

	float timeKillAll;
	bool choose;
	static Game *game;
	static UI* ui;
	static int Countdown;;
public:
	int state;
	GameState() {}
	~GameState() {}
	virtual void Render() {};
	virtual void DestroyAll() = 0;


	virtual void Update(DWORD gameTime) {};
	virtual bool GetChangingState() { return changeState; };
	virtual void SetChangingState(bool status) { changeState = status; }

	virtual bool CameraFollowHandle(float gameTime) = 0;
	void setGame(Game* game) { this->game = game; }

};
#endif __GAMESTATE_H__
