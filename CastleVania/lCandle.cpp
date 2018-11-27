#include "lCandle.h"



void lCandle::Render()
{
	animations[0]->Render(x, y);
}

void lCandle::LoadResources()
{

	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();
	Textures * textures = Textures::GetInstance();

	textures->Add(ID_TEX_LCANDLE, L"Resource\\sprites\\Ground\\0.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texCandle = textures->Get(ID_TEX_LCANDLE);
	sprites->Add(40001, 0, 0, 32, 64, texCandle);
	sprites->Add(40002, 32, 0, 64, 64, texCandle);
	LPANIMATION ani;
	ani = new Animation(100);		// lCandle
	ani->Add(40001);
	ani->Add(40002);
	animations->Add(401, ani);
}

void lCandle::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + LCANDLE_WIDTH;
	b = y + LCANDLE_HEIGHT;
}

