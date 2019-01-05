#include "BatIntro.h"

void BatIntro::Render()
{
	animations[0]->Render(x, y);
}

void BatIntro::LoadResources()
{

	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();
	Textures * textures = Textures::GetInstance();

	textures->Add(ID_TEX_BAT_INTRO, L"Resource\\sprites\\bat.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texBatIntro = textures->Get(ID_TEX_BAT_INTRO);
	sprites->Add(100001, 0, 0, 16, 16, texBatIntro);
	sprites->Add(100002, 16, 0, 32, 16, texBatIntro);
	LPANIMATION ani;
	ani = new Animation(100);		// Ground
	ani->Add(100001);
	ani->Add(100002);
	animations->Add(1001, ani);
	AddAnimation(1001);
}

void BatIntro::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	GameObject::Update(dt);
	x += dx;
	y += dy;
}

void BatIntro::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{

}