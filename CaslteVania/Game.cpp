#include "Game.h"
Game::Game()
{
	gDevice = NULL;
	gameTime = NULL;
}


Game::~Game()
{
	SAFE_DELETE(gDevice);
	SAFE_DELETE(cam);
	SAFE_DELETE(gameTime);
}

bool Game::Initialize(HWND hWnd, int width, int height)
{
	if (!InitDirectInput() || !InitKeyboard(hWnd))
		return false;

	gameTime = new GameTime();
	if (!gameTime->Initialize())
		return false;

	stateManager = new StateManager();

	//timeStart = GetTickCount();
	if (!stateManager->Initialize(hWnd))
		return false;

	stateManager->LoadState(GAME_PLAY_STATE_ONE);

	return true;
}

void Game::Run()
{
	//this->TimeHandle();

	gameTime->Update();

	Update(gameTime->m_elapsedGameTime);
	Draw();
}

// Update our sprites and other game logics
void Game::Update(float _gameTime)
{
	PollKeyboard();

	stateManager->Update(_gameTime);
}

void Game::Draw()
{
	stateManager->Render();
}

