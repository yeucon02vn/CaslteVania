#pragma once
#include "Graphics.h"
#include "Input.h"
#include "Sprite.h"
#include "Simon.h"
#include "Collider.h"
#include "GameTime.h"
#include "StateManager.h"
class Game
{
private:
	Graphics* gDevice;
	Camera* cam;

	DWORD timeStart;
	DWORD timeNow;

	GameTime* gameTime;
	StateManager* stateManager;
public:
	Game();
	~Game();

	bool Initialize(HWND hWnd, int width, int height);
	void Run();
	void Update(float _gameTime);
	void Draw();
};


