#include "Bullets.h"



void Bullets::Render()
{
	if(nx > 0)
		animations[0]->Render(x, y);
	else
		animations[1]->Render(x, y);
}

void Bullets::LoadResources()
{

	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();
	Textures * textures = Textures::GetInstance();


	textures->Add(ID_TEX_BULLETSL, L"Resource\\sprites\\Enemies\\FIREBALLL.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texBulletL = textures->Get(ID_TEX_BULLETSL);

	textures->Add(ID_TEX_BULLETSR, L"Resource\\sprites\\Enemies\\FIREBALLR.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texBulletR = textures->Get(ID_TEX_BULLETSR);


	sprites->Add(1700001, 0, 0, 14, 12, texBulletR);
	sprites->Add(1700002, 0, 0, 14, 12, texBulletL);

	LPANIMATION ani;

	ani = new Animation(100);
	ani->Add(1700001);
	animations->Add(1701, ani);

	ani = new Animation(100);		// Ground
	ani->Add(1700002);
	animations->Add(1702, ani);

	//vx = ITEM_BULLET_SPEED;
	AddAnimation(1701);
	AddAnimation(1702);
}


void Bullets::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BULLET_BBOX_WIDTH;
	b = y + BULLET_BBOX_HEIGHT - 8;
}

void Bullets::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (nx < 0) vx = -ITEM_BULLET_SPEED - 0.02f;
	else vx = ITEM_BULLET_SPEED + 0.02f;

	GameObject::Update(dt);
	x += dx;
}

void Bullets::setPositionBullet(float x, float y)
{
	if (nx > 0)
		x += 50;
	SetPosition(x, y);
}
