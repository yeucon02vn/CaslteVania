#include "Stair.h"



void Stair::Render()
{
	if(nx < 0)
		for(int i = 0; i < count; i++)
			animations[0]->Render(x + i*32, y- i*32);
	else
		for (int i = 0; i < count; i++)
			animations[0]->Render(x + i * 32, y + i * 32);
}

void Stair::LoadResources()
{

	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();
	Textures * textures = Textures::GetInstance();

	textures->Add(ID_TEX_STAIR_RIGHT, L"Resource\\sprites\\Ground\\3_.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texStairR = textures->Get(ID_TEX_STAIR_RIGHT);
	sprites->Add(1500001, 0, 0, 32, 32, texStairR);


	textures->Add(ID_TEX_STAIR_LEFT, L"Resource\\sprites\\Ground\\3.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texStairL = textures->Get(ID_TEX_STAIR_LEFT);
	sprites->Add(1500002, 0, 0, 32, 32, texStairL);


	LPANIMATION ani;
	ani = new Animation(100);		// Stair
	ani->Add(1500001);
	animations->Add(1501, ani);

	ani = new Animation(100);		// Stair
	ani->Add(1500002);
	animations->Add(1502, ani);

}

void Stair::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y ;
	r = x + STAIR_WIDTH ;
	b = y + STAIR_HEIGHT;
}

