#include "GamePlayStateOne.h"



GamePlayStateOne::GamePlayStateOne()
{
}


GamePlayStateOne::~GamePlayStateOne()
{
}

bool GamePlayStateOne::Initialize(Graphics *graphics)
{
	this->gDevice = graphics->GetDevice();

	cam = new Camera(0, GAME_HEIGHT);

	sprite = new Sprite();
	if (!sprite->Initialize(gDevice, LEVEL_ONE_BG))
		return false;

	castleSprite = new Sprite(1408, 347);
	if (!castleSprite->Initialize(gDevice, CASTLE_SPRITE))
		return false;

	tileMap = new TileMap(1536, 392, sprite, 64, 64);
	tileMap->LoadListTileFromFile(LEVEL_ONE_MATRIX_BG);

	cameraObject = new GameObject();
	cameraObject->Initialize(gDevice, SIMON_SPRITE, cam->GetCameraPosition().x, cam->GetCameraPosition().y, 5);

	leftCamera = new Ground(2, 450);
	leftCamera->Initialize(gDevice, "Resource\\sprites\\Ground\\0.png", cam->GetCameraPosition().x - 2, cam->GetCameraPosition().y, TAG_GROUND);

	rightCamera = new Ground(2, 450);
	rightCamera->Initialize(gDevice, "Resource\\sprites\\Ground\\0.png", cam->GetCameraPosition().x + GAME_WIDTH, cam->GetCameraPosition().y, TAG_GROUND);

	quadTree = new QuadTree(gDevice, cam);
	quadTree->Load("Resource\\sprites\\QuadTree\\lv1.txt");

	list = new std::vector<GameObject*>();


	simon = new Simon();
	if (!simon->Initialize(gDevice, SIMON_SPRITE, 610, 91, TAG_SIMON))
		return false;
	simon->SetPosition(100, 150);
	simon->Reload();

	changeState = false;



	return true;
}


void GamePlayStateOne::Update(float gameTime)
{
	time += gameTime;

	if (simon->GetPosition().x >= GAME_WIDTH / 2 && simon->GetPosition().x <= 1536 - GAME_WIDTH / 2 - 32)
	{
		D3DXVECTOR3 currentCamera = cam->GetCameraPosition();
		currentCamera.x += simon->GetVelocity().x * gameTime;
		cam->SetCameraPosition(currentCamera.x, currentCamera.y);
	}

	cameraObject->SetPosition(cam->GetCameraPosition());
	cameraObject->SetRegion(0, GAME_WIDTH, 0, -GAME_HEIGHT);

	//khong cho simon di ra khoi camera
	leftCamera->SetPosition(cam->GetCameraPosition().x - 2, cam->GetCameraPosition().y);
	leftCamera->SetBox(leftCamera->GetPosition().x, leftCamera->GetPosition().y, 2, GAME_HEIGHT, 0, 0);

	rightCamera->SetPosition(cam->GetCameraPosition().x + GAME_WIDTH, cam->GetCameraPosition().y);
	rightCamera->SetBox(rightCamera->GetPosition().x, rightCamera->GetPosition().y, 2, GAME_HEIGHT, 0, 0);

	list->clear();
	quadTree->GetObjectList(list, cameraObject->GetRegion());
	for (auto i = list->begin(); i != list->end(); i++)
	{
		if (!(*i)->IsEnable())
		{

			quadTree->Remove((*i));
		}
		else
			(*i)->Update(gameTime);
	}


	simon->KeyBoardHandle(gameTime);
	simon->Update(gameTime);
	simon->CheckCollider(gameTime, list);
	simon->CheckColliderWith(gameTime, leftCamera);
	simon->CheckColliderWith(gameTime, rightCamera);

	if (IsKeyPress(DIK_M))
		SetChangingState(true);

	if (simon->GetPosition().x > 1300 && simon->GetPosition().x < 1400)
	{
		simon->SetVelocity(D3DXVECTOR3(0, 0, 0));
		simon->SetPosition(simon->GetPosition().x + 50 * gameTime,
			simon->GetPosition().y);
		simon->SetAction(MOVE);
		simon->SetCanControlKeyboard(false);

	}
	else if (simon->GetPosition().x > 1400)
	{
		SetChangingState(true);
	}
}

void GamePlayStateOne::Render()
{
	tileMap->Draw(cam);
	for (auto i = list->begin(); i != list->end(); i++)
	{
		(*i)->isAdded = false;
		(*i)->Render(cam);
	}

	simon->Render(cam);

	castleSprite->Render(cam);
}

bool GamePlayStateOne::GetChangingState()
{
	return GameState::GetChangingState();
}

void GamePlayStateOne::SetChangingState(bool status)
{
	GameState::SetChangingState(status);
}

void GamePlayStateOne::DestroyAll()
{
	delete(simon);
	delete(tileMap);
	delete(ground);
	delete(cameraObject);
	delete(listObject);
	delete(cam);
}