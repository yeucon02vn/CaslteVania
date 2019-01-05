#include "Helicop.h"

void Helicop::LoadResources()
{
	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();
	Textures * textures = Textures::GetInstance();

	textures->Add(ID_TEX_HELICOP, L"Resource\\sprites\\helicopter.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texHelicop = textures->Get(ID_TEX_HELICOP);
	sprites->Add(90001, 0, 0, 64, 28, texHelicop);

	LPANIMATION ani;
	ani = new Animation(100);		// Ground
	ani->Add(90001);
	animations->Add(901, ani);
	AddAnimation(901);
}

void Helicop::Render()
{
	animations[0]->Render(x,y);
}

void Helicop::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	//vx = -HELICOP_SPEED;

	GameObject::Update(dt);
	x += dx;
}

void Helicop::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{

}