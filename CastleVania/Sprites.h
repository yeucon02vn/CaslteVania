#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "Game.h"
#include "debug.h"

using namespace std;

class Sprite
{
	int id;				// Sprite ID in the sprite database

	int left;
	int top;
	int right;
	int bottom;

	LPDIRECT3DTEXTURE9 texture;
public:
	Sprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	int getWidth();
	int getHeight();
	void Draw(float x, float y, RECT rect, int alpha);
	void Draw(float x, float y, int alpha = 255);
	//void DrawCamera(float x, float y, Camera *cam, int alpha);
};

typedef Sprite * LPSPRITE;

/*
Manage sprite database
*/
class Sprites
{
	static Sprites * __instance;

	unordered_map<int, LPSPRITE> sprites;

public:
	void Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(int id);

	static Sprites * GetInstance();
};



