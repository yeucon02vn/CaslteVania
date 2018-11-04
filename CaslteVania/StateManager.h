#pragma once
#include "Graphics.h"
#include "GamePlayStateOne.h"
#include "Input.h"

class StateManager
{
private:
	Graphics* gDevice;
	GameState* gameState;
	int stateID;
public:
	StateManager();
	~StateManager();
	bool Initialize(HWND hwnd);
	void LoadState(int stateID);
	void Render();
	void Update(float gameTime);
};

