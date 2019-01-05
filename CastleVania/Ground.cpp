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

	textures->Add(ID_TEX_GROUND2, L"Resource\\sprites\\Ground\\Brick.png", D3DCOLOR_XRGB(255, 255, 255));
	LPDIRECT3DTEXTURE9 texGround2 = textures->Get(ID_TEX_GROUND2);
	sprites->Add(30003, 0, 0, 32, 32, texGround2);

	textures->Add(ID_TEX_GROUND1, L"Resource\\sprites\\Ground\\2.png", D3DCOLOR_XRGB(255, 255, 255));
	LPDIRECT3DTEXTURE9 texGround1 = textures->Get(ID_TEX_GROUND1);
	sprites->Add(30002, 0, 0, 32, 32, texGround1);

	


	LPANIMATION ani;

	ani = new Animation(100);		// Ground
	ani->Add(30002);
	animations->Add(302, ani);

	ani = new Animation(100);		// Ground
	ani->Add(30003);
	animations->Add(303, ani);
}

void Ground::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + GROUND_WIDTH;
	b = y + GROUND_HEIGHT;
}

