#include "GameMenu.h"

GameMenu::GameMenu()
{
	LoadResources();
}


GameMenu::~GameMenu()
{
}

void GameMenu::LoadResources()
{

	tileMap = new TileMap(MENU_STATE);

	animation = new TitleAnimation();
	animation->LoadResources();
	animation->SetPosition(446, 255);
}


void GameMenu::Render()
{
	tileMap->Draw();
	animation->Render();
}

void GameMenu::Update(DWORD gameTime)
{
	Control();
}



void GameMenu::DestroyAll() 
{
	delete(tileMap);
	delete(animation);
}

void GameMenu::Control()
{
	if (IsKeyPress(DIK_RETURN))
		SetChangingState(true);
}
