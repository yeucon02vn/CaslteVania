#include "GameIntro.h"

GameIntro::GameIntro()
{
	LoadResources();
}


GameIntro::~GameIntro()
{
}

void GameIntro::LoadResources()
{

	timeDelay = 0;
	tileMap = new TileMap(INTRO_STATE); // Resource\\sprites\\helicopter.png

	helicopter = new Helicop();
	helicopter->LoadResources();
	helicopter->SetPosition(552, 98);
	helicopter->SetSpeed(-0.01f, 0);

	for (int i = 0; i < 2; i++)
	{
		bat[i] = new BatIntro();
		bat[i]->LoadResources();
	}
	bat[0]->SetPosition(82, 255);
	bat[0]->SetSpeed(0.02f, -0.01f);

	bat[1]->SetPosition(480, 48);
	bat[1]->SetSpeed(-0.02f, 0.005f);

	simon = new Simon();
	simon->LoadResources();
	simon->isIntro = true;
	simon->SetPosition(600, 370);

	ground = new Ground0();
	ground->LoadResources();

	for (int i = 0; i < 13; i++)
	{
		ground = new Ground0();
		ground->AddAnimation(301);
		ground->SetPosition(250 + i * 32, 480 - 48);
		objects.push_back(ground);
	}

}


void GameIntro::Render()
{

	tileMap->Draw();
	
	for (int i = 0; i < 13; i++)
	{
		objects[i]->Render();
	}

	helicopter->Render();

	bat[0]->Render();
	bat[1]->Render();

	simon->Render();
}

void GameIntro::Update(DWORD gameTime)
{
	// De update cai animation con doi bay bay sau


	bat[0]->Update(gameTime);
	bat[1]->Update(gameTime);
	helicopter->Update(gameTime);
	simon->GetPosition(pos.x, pos.y);
	simon->vy = 0;
	if ( pos.x >   SCREEN_WIDTH / 2 - 35)
	{
		simon->SetSpeed(-0.001f, 0);
		simon->setNx(-1);
		simon->SetState(SIMON_STATE_WALK);
		
	}
	else
	{
		simon->SetSpeed(0, 0);
		simon->SetPosition(pos.x, pos.y);
		simon->setBack(true);
		timeDelay += gameTime;
		if (timeDelay >= 350)
		{
			SetChangingState(true);
			
		}
	}

	simon->Update(gameTime, &objects);
}

void GameIntro::DestroyAll()
{
	SAFE_DELETE(ground);
	SAFE_DELETE(tileMap);
	SAFE_DELETE(helicopter);
	SAFE_DELETE(bat[0]);
	SAFE_DELETE(bat[1]);
	objects.clear();
}


