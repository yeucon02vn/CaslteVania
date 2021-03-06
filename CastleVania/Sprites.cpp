#include "Sprites.h"


Sprite::Sprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
}

Sprites * Sprites::__instance = NULL;

Sprites *Sprites::GetInstance()
{
	if (__instance == NULL) __instance = new Sprites();
	return __instance;
}

void Sprite::Draw(float x, float y, int alpha)
{
	Game * game = Game::GetInstance();
	game->Draw(x, y, texture, left, top, right, bottom, alpha);
}

void Sprite::Draw(float x, float y, RECT rect, int alpha)
{
	Game * game = Game::GetInstance();
	game->Draw(x, y, texture, rect.left, rect.top, rect.right, rect.bottom, alpha);
}

void Sprite::DrawBoard(float x, float y, int alpha)
{
	Game * game = Game::GetInstance();
	game->DrawBoard(x, y, texture, left, top, right, bottom, alpha);
}

int Sprite::getWidth()
{
	return this->right - this->left;
}

int Sprite::getHeight()
{
	return this->bottom - this->top;
}


void Sprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new Sprite(id, left, top, right, bottom, tex);
	sprites[id] = s;
}

LPSPRITE Sprites::Get(int id)
{
	return sprites[id];
}



