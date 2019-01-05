#include "mCandle.h"



void mCandle::Render()
{
	animations[0]->Render(x, y);
}

void mCandle::LoadResources()
{

	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();
	Textures * textures = Textures::GetInstance();

	textures->Add(ID_TEX_MCANDLE, L"Resource\\sprites\\Ground\\1.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texmCandle = textures->Get(ID_TEX_MCANDLE);
	sprites->Add(40003, 0, 0, 16, 32, texmCandle);
	sprites->Add(40004, 16, 0, 32, 32, texmCandle);
	LPANIMATION ani;
	ani = new Animation(100);		// lCandle
	ani->Add(40003);
	ani->Add(40004);
	animations->Add(402, ani);
}

void mCandle::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + LCANDLE_WIDTH;
	b = y + LCANDLE_HEIGHT;
}
