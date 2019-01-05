#pragma once
#include "GameMenu.h"
#include "GameIntro.h"
#include "GameState1.h"
#include "GameState2.h"

class StateManager
{
private:
	GameState* gameState;
	int stateID;
	Game* game;
public:
	StateManager();
	~StateManager();
	void LoadState(int stateID);
	void NextStateLevel();
	void Render();
	void Update(float gameTime);
	int getState() { return stateID; }
	void Init(Game* game)
	{
		gameState->setGame(game);
	}
};
