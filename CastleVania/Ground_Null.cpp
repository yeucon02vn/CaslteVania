#include "Ground_Null.h"



void Ground0::Render()
{
	animations[0]->Render(x, y);
}

void Ground0::LoadResources()
{

	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();
	Textures * textures = Textures::GetInstance();


	textures->Add(ID_TEX_GROUND, L"Resource\\sprites\\Ground\\NULL.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texGround = textures->Get(ID_TEX_GROUND);
	sprites->Add(30001, 0, 0, 32, 32, texGround);

	LPANIMATION ani;
	ani = new Animation(100);		// Ground
	ani->Add(30001);
	animations->Add(301, ani);
}


void Ground0::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + GROUND_WIDTH;
	b = y + GROUND_HEIGHT;
}