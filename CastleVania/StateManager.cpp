
#include "StateManager.h"

///*CHUYEN CAC THANH PHAN CO BAN TU GAME.CPP SANG*/

StateManager::StateManager()
{
}


StateManager::~StateManager()
{
}


void StateManager::LoadState(int stateID)
{
	switch (stateID)
	{
	case MENU_STATE:
		gameState = new GameMenu();
		gameState->state = stateID;
		this->stateID = stateID;
		break;
	case INTRO_STATE:
		delete(gameState);
		gameState = new GameIntro();
		gameState->state = stateID;
		this->stateID = stateID;
		break;
	case STATE_LV1:
		delete(gameState);
		gameState = new GameState1();
		gameState->state = stateID;
		this->stateID = stateID;
		break;
	case STATE_LV2:
		delete(gameState);
		gameState = new GameState2();

		gameState->state = stateID;
		this->stateID = stateID;
		break;
	default:
		break;
	}
}

void StateManager::NextStateLevel()
{
	stateID++;
}
void StateManager::Render()
{
		gameState->Render();
}

void StateManager::Update(float gameTime)
{
	if (gameState->GetChangingState())
	{
		if (stateID != MENU_STATE)
		{
			gameState->DestroyAll();
		}
		NextStateLevel();
		LoadState(stateID);
		gameState->SetChangingState(false);
	}
	gameState->Update(gameTime);
}

