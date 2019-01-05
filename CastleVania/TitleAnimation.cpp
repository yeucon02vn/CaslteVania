#include "TitleAnimation.h"



void TitleAnimation::Render()
{
	animations[0]->Render(x, y);
}

void TitleAnimation::LoadResources()
{

	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();
	Textures * textures = Textures::GetInstance();

	textures->Add(ID_TEX_TITLE_ANIMATION, TITLE_ANIMATION, D3DCOLOR_XRGB(255, 255, 255));
	LPDIRECT3DTEXTURE9 texTitle = textures->Get(ID_TEX_TITLE_ANIMATION);

	sprites->Add(60001, 0, 0, 158, 123, texTitle);
	sprites->Add(60002, 158, 0, 316, 123, texTitle);
	sprites->Add(60003, 316, 0, 474, 123, texTitle);
	sprites->Add(60004, 474, 0, 632, 123, texTitle);
	sprites->Add(60005, 632, 0, 790, 123, texTitle);

	sprites->Add(60006, 0, 123, 158, 246, texTitle);
	sprites->Add(60007, 158, 123, 316, 246, texTitle);
	sprites->Add(60008, 316, 123, 474, 246, texTitle);
	sprites->Add(60009, 474, 123, 632, 246, texTitle);
	sprites->Add(60010, 632, 123, 790, 246, texTitle);

	sprites->Add(60011, 0, 246, 158, 369, texTitle);
	sprites->Add(60012, 158, 246, 316, 369, texTitle);
	sprites->Add(60013, 316, 246, 474, 369, texTitle);
	sprites->Add(60014, 474, 246, 632, 369, texTitle);
	sprites->Add(60015, 632, 246, 790, 369, texTitle);

	LPANIMATION ani;
	ani = new Animation(100);		
	ani->Add(60001);
	ani->Add(60002);
	ani->Add(60003);
	ani->Add(60004);
	ani->Add(60005);
	ani->Add(60006);
	ani->Add(60007);
	ani->Add(60008);
	ani->Add(60009);
	ani->Add(60010);
	ani->Add(60011);
	ani->Add(60012);
	ani->Add(60013);
	ani->Add(60014);
	ani->Add(60015);
	animations->Add(601, ani);

	AddAnimation(601);
}

void TitleAnimation::GetBoundingBox(float &l, float &t, float &r, float &b)
{

}

