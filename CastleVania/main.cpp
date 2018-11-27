/* =============================================================
INTRODUCTION TO GAME PROGRAMMING SE102

SAMPLE 04 - COLLISION

This sample illustrates how to:

1/ Implement SweptAABB algorithm between moving objects
2/ Implement a simple (yet effective) collision frame work

Key functions:
CGame::SweptAABB
CGameObject::SweptAABBEx
CGameObject::CalcPotentialCollisions
CGameObject::FilterCollision

CGameObject::GetBoundingBox

================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "Ground.h"
#include "Simon.h"
#include "TileMap.h"
#include "lCandle.h"
#include "Items.h"	
Camera *cam;
Game *game;
Simon *simon;
vector<LPITEMS> list_items;
vector<LPGAMEOBJECT> objects;
TileMap *maps;
Ground * ground;
D3DXVECTOR2 position;
lCandle *lcandle;
Items * item;

class SampleKeyHander : public KeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

SampleKeyHander * keyHandler;

void SampleKeyHander::OnKeyDown(int KeyCode)
{
	if (simon->KillAllKey == true)
		return;
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_Z:
		if (simon->checkFight() == true)
			return;
		if (simon->checkFight() == false && (simon->checkJump() == true || simon->GetState() == SIMON_STATE_IDLE))
			simon->SetState(SIMON_STATE_ATK);
		if (simon->checkFight() == false && simon->checkSit() == true)
			simon->SetState(SIMON_STATE_S_ATK);
		break;
	case DIK_SPACE:
		if (simon->checkGround() == true && simon->checkSit() == false)
			simon->SetState(SIMON_STATE_JUMP);
		break;
	case DIK_X:
		if (simon->checkWeapon() == false)
			return;
		if (simon->checkWeapon() == true)
			simon->SetState(SIMON_STATE_USE_ITEM);
	}
}

void SampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void SampleKeyHander::KeyState(BYTE *states)
{
	if (simon->KillAllKey == true)
		return;
	if (simon->GetState() == SIMON_STATE_DIE || simon->checkFight() == true || simon->checkJump() == true) return;
	if (game->IsKeyDown(DIK_RIGHT) && simon->checkSit() == false)
	{
		simon->setNx(1);
		simon->SetState(SIMON_STATE_WALK);
	}
	else if (game->IsKeyDown(DIK_LEFT) && simon->checkSit() == false)
	{	
		simon->setNx(-1);
		simon->SetState(SIMON_STATE_WALK);
	}
	else if (game->IsKeyDown(DIK_DOWN ))
		simon->SetState(SIMON_STATE_SIT);
	else 
		simon->SetState(SIMON_STATE_IDLE);

}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
Load all game resources
In this example: load textures, sprites, animations and mario object

TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/
void LoadResources()
{
	maps = new TileMap();

	simon = new Simon();
	simon->LoadResources();
	simon->SetPosition(20, 100);
	
	objects.push_back(simon);


	ground = new Ground();
	ground->LoadResources();

	for (int i = 0; i < 48; i++)
	{
		ground = new Ground();
		ground->AddAnimation(301);
		ground->SetPosition(0 + i*32, 480-32);
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
		lcandle->SetPosition(380 + i*180, 480 - 96);
		objects.push_back(lcandle);
	}
	
}

/*
Update world status for this frame
dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	vector<LPGAMEOBJECT> coObjects;
	for (int i = 1; i < objects.size() + list_items.size(); i++)
	{
		if (i <= objects.size() - 1)
			coObjects.push_back(objects[i]); 
		else
			coObjects.push_back(list_items[i - objects.size()]); 
	}

	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->isEnable == true)
			objects[i]->Update(dt, &coObjects);
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
				list_items.push_back(item);
			}
			objects.erase(objects.begin() + i);
		}
	}

	for (int i = 0; i < list_items.size(); i++)
	{
		if(list_items[i]->isEnable == true)
			list_items[i]->Update(dt, &coObjects);
		else
			list_items.erase(list_items.begin() + i);
	}
	
	if (simon->x >= SCREEN_WIDTH / 2 && simon->x <= 1536 - SCREEN_WIDTH / 2 -32)
	{
		simon->getX(position.x);
		position.x -= SCREEN_WIDTH / 2;
		game->setCamPosition(position.x, 0);
		
	}

	if (simon->x > 1320 && simon->x < 1420)
	{
		simon->SetState(SIMON_STATE_WALK);
		simon->KillAllKey = true;
	}
	if (simon->x > 1430)
	{
		simon->KillAllKey = false;
	}
}

/*
Render a frame
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();
	
	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		maps->DrawMap(position);
		for (int i = 0; i < objects.size(); i++)
		{
			if (objects[i]->isEnable == true)
			{
				objects[i]->Render();
			}
		}
		for (int i = 0; i < list_items.size(); i++)
		{
			if (list_items[i]->isEnable == true)
			{
				list_items[i]->Render();
			}
		}
		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}


HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow,int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wcx;

	wcx.cbSize = sizeof(wcx);
	wcx.style = CS_HREDRAW | CS_VREDRAW;
	wcx.lpfnWndProc = WinProc;
	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.hInstance = hInstance;
	wcx.hIcon = NULL;
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcx.lpszMenuName = NULL;
	wcx.lpszClassName = WINDOW_CLASS_NAME;
	wcx.hIconSm = NULL;

	if (RegisterClassEx(&wcx) == 0)
		return false;

	DWORD style;
	if (FULLSCREEN)
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	else
		style = WS_OVERLAPPEDWINDOW;

	HWND hWnd = CreateWindow(
		WINDOW_CLASS_NAME,
		MAIN_WINDOW_TITLE,
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		(HWND)NULL,
		(HMENU)NULL,
		hInstance,
		(LPVOID)NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	if (!FULLSCREEN)
	{
		RECT clientRect;
		GetClientRect(hWnd, &clientRect);
		MoveWindow(hWnd,
			0,
			0,
			SCREEN_WIDTH + (SCREEN_WIDTH - clientRect.right),
			SCREEN_HEIGHT + (SCREEN_HEIGHT - clientRect.bottom),
			TRUE);
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= MAX_TIME_PER_FRAME)
		{
			frameStart = now;

			game->ProcessKeyboard();

			Update(dt);
			Render();
		}
		else
			Sleep(MAX_TIME_PER_FRAME - dt);
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);
	cam = new Camera(20);
	game = Game::GetInstance();
	game->Init(hWnd);

	keyHandler = new SampleKeyHander();
	game->InitKeyboard(keyHandler);


	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}