#include "Door.h"



void Door::Render()
{
	if(state == 0)
		animations[0]->Render(x, y);
	else if (state == 1)
		animations[1]->Render(x, y);
	else
		animations[2]->Render(x, y);
}

void Door::LoadResources()
{

	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();
	Textures * textures = Textures::GetInstance();



	textures->Add(ID_TEX_DOOR, L"Resource\\sprites\\Ground\\10.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texDoor = textures->Get(ID_TEX_DOOR);
	sprites->Add(30004, 0, 0, 16, 96, texDoor);

	textures->Add(ID_TEX_DOOR1, L"Resource\\sprites\\Ground\\Gate.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texDoor1 = textures->Get(ID_TEX_DOOR1);
	sprites->Add(30005, 48, 0, 80, 96, texDoor1);

	sprites->Add(30006, 96, 0, 192, 96, texDoor1);

	LPANIMATION ani;

	ani = new Animation(100);
	ani->Add(30004);
	animations->Add(304, ani);

	ani = new Animation(100);
	ani->Add(30005);
	animations->Add(305, ani);

	ani = new Animation(100);
	ani->Add(30006);
	animations->Add(306, ani);

	AddAnimation(304);
	AddAnimation(305);
	AddAnimation(306);
}

void Door::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + DOOR_WIDTH;
	b = y + DOOR_HEIGHT;
}

