#include "Ground.h"



void Ground::Render()
{
	animations[0]->Render(x, y);
}

void Ground::LoadResources()
{

	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();
	Textures * textures = Textures::GetInstance();

	textures->Add(ID_TEX_GROUND, L"Resource\\sprites\\Ground\\2.png", D3DCOLOR_XRGB(255, 255, 255));
	LPDIRECT3DTEXTURE9 texGround = textures->Get(ID_TEX_GROUND);
	sprites->Add(30001, 0, 0, 32, 32, texGround);

	LPANIMATION ani;
	ani = new Animation(100);		// Ground
	ani->Add(30001);
	animations->Add(301, ani);
}

void Ground::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + GROUND_WIDTH;
	b = y + GROUND_HEIGHT;
}

