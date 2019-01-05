#pragma once
#include "GameState.h"
#include "Sprites.h"
#include "TitleAnimation.h"
#include "KeyEventHandler.h"

class GameMenu : public GameState
{
private:
	
	TileMap *tileMap;
	TitleAnimation *animation;
public:
	GameMenu();
	~GameMenu();
	void LoadResources();
	void Render();
	void Update(DWORD gameTime);
	void DestroyAll();
	bool GetChangingState() { return GameState::GetChangingState(); }
	void SetChangingState(bool status) { GameState::SetChangingState(status); }
	bool CameraFollowHandle(float gameTime) { return true; }
	void Control();
};