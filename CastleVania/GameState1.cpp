#include "GameState1.h"


GameState1::GameState1()
{
	LoadResources();
}


GameState1::~GameState1()
{
}


void GameState1::LoadResources()
{
	timeDelay = 0;
	changeState = false;
	simon->setBack(false);
	

	tileMap = new TileMap(STATE_LV1);
	simon->isIntro = false;
	simon->SetPosition(20, 380);

	ui = new UI();
	ui->setDevice(game->GetDirect3DDevice());
	ui->setSimon(simon);
	ui->LoadResources();
	time = 300;

	objects.push_back(simon);

	ground = new Ground();
	ground->LoadResources();



	for (int i = 0; i < 48; i++)
	{
		ground = new Ground();
		ground->AddAnimation(302);
		ground->SetPosition(0 + i * 32, 480 - 30);
		objects.push_back(ground);
	}

	lcandle = new lCandle();
	lcandle->LoadResources();

	item = new Items();
	item->LoadResources();

	for (int i = 0; i < 6; i++)
	{
		lcandle = new lCandle();
		lcandle->isDropItem = true;
		lcandle->AddAnimation(401);
		lcandle->SetPosition(380 + i * 180, 480 - 96);
		objects.push_back(lcandle);
	}
	Countdown = 0;
}



void GameState1::Update(DWORD gameTime)
{
	
	time = 300 - Countdown/100.;
	ui->Update(64, time, 3, 1);
	Countdown++;
	if(!NoControl)
		Control();
	
	
	vector<LPGAMEOBJECT> listObject;
	for (int i = 1; i < objects.size() + listItem.size(); i++)
	{
		if (i <= objects.size() - 1)
			listObject.push_back(objects[i]);
		else
			listObject.push_back(listItem[i - objects.size()]);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->isEnable == true)
			objects[i]->Update(gameTime, &listObject);
		else
		{
			if (objects[i]->isDropItem == true)
			{
				item = new Items();
				item->SetPosition(objects[i]->x, objects[i]->y);// inaccessible
				if (simon->getTypeofWhip() == WHIP_LV2)
				{
					item->setLv2();
				}
				item->Random();
				listItem.push_back(item);
			}
			objects.erase(objects.begin() + i);
		}
	}

	for (int i = 0; i < listItem.size(); i++)
	{
		if (listItem[i]->isEnable == true)
			listItem[i]->Update(gameTime, &listObject);
		else
			listItem.erase(listItem.begin() + i);
	}

	if (simon->x >= SCREEN_WIDTH / 2 && simon->x <= 1536 - SCREEN_WIDTH / 2 - 32)
	{
		simon->getX(pos.x);
		pos.x -= SCREEN_WIDTH / 2;
		game->setCamPosition(pos.x, 0);
	}

	if (simon->x > 1280 && simon->x < 1420)
	{
		simon->SetState(SIMON_STATE_WALK);
		NoControl = true;
		if (simon->x > 1350)
			SetChangingState(true);

	}

}

void GameState1::Render()
{
	
	tileMap->DrawMap(pos);
	ui->Render();
	for (int i = 0; i < objects.size(); i++)
	{
			objects[i]->Render();
	}
	for (int i = 0; i < listItem.size(); i++)
	{
			listItem[i]->Render();
	}
}

bool GameState1::GetChangingState()
{
	return GameState::GetChangingState();
}

void GameState1::SetChangingState(bool status)
{
	GameState::SetChangingState(status);
}

void GameState1::DestroyAll()
{
	//delete(simon);
	SAFE_DELETE(tileMap);
	SAFE_DELETE(ground);
	SAFE_DELETE(item);
	SAFE_DELETE(lcandle);
	objects.clear();
	listItem.clear();
}

void GameState1::Control()
{
	if (simon->GetState() == SIMON_STATE_DIE || simon->checkFight() == true  || simon->checkEffect() == true) 
		return;
	
	if (IsKeyDown(DIK_UP))
	{
		if (IsKeyPress(DIK_Z))
		{
			if (simon->checkUseItem() == true)
				return;
			if (simon->checkWeapon() == false)
				return;
			if (simon->checkWeapon() == true)
				simon->SetState(SIMON_STATE_USE_ITEM);

		}
	}
	else if (IsKeyPress(DIK_Z))
	{
		if (simon->checkFight() == true )
			return;
		if (simon->checkFight() == false && (simon->checkJump() == true || simon->GetState() == SIMON_STATE_IDLE))
			simon->SetState(SIMON_STATE_ATK);
		if (simon->checkFight() == false && simon->checkSit() == true)
			simon->SetState(SIMON_STATE_S_ATK);
	}
	else if (IsKeyPress(DIK_SPACE))
	{
		if (simon->checkGround() == true && simon->checkSit() == false)
			simon->SetState(SIMON_STATE_JUMP);
	}
	/*else if (IsKeyPress(DIK_X))
	{
		if (simon->checkUseItem() == true)
			return;
		if (simon->checkWeapon() == false)
			return;
		if (simon->checkWeapon() == true)
			simon->SetState(SIMON_STATE_USE_ITEM);
	}*/
	else if (IsKeyDown(DIK_RIGHT) && simon->checkSit() == false)
	{
		if (simon->checkJump() == true)
			return;
		simon->setNx(1);
		simon->SetState(SIMON_STATE_WALK);
	}
	else if (IsKeyDown(DIK_LEFT) && simon->checkSit() == false)
	{
		if (simon->checkJump() == true)
			return;
		simon->setNx(-1);
		simon->SetState(SIMON_STATE_WALK);
	}
	else if (IsKeyDown(DIK_DOWN))
	{
		if (simon->checkJump() == true)
			return;
		simon->SetState(SIMON_STATE_SIT);
	}
	else
	{
		if (simon->checkJump() == true)
			return;
		simon->SetState(SIMON_STATE_IDLE);
	}
}