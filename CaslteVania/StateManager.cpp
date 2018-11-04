#include "StateManager.h"
StateManager::StateManager()
{
}


StateManager::~StateManager()
{
}

bool StateManager::Initialize(HWND hwnd)
{
	gDevice = new Graphics();
	if (!gDevice->Initialize(hwnd))
		return false;
	return true;
}

void StateManager::LoadState(int stateID)
{
	gameState = new GamePlayStateOne();
	if (!gameState->Initialize(gDevice))
		return;
	gameState->state = stateID;
	this->stateID = stateID;

}


void StateManager::Render()
{
	gDevice->Clear();
	gDevice->Begin();

	gameState->Render();

	gDevice->End();
	gDevice->Present();
}

void StateManager::Update(float gameTime)
{
	if (gameState->GetChangingState())
	{
		LoadState(stateID);
		gameState->SetChangingState(false);
	}

	gameState->Update(gameTime);
}
