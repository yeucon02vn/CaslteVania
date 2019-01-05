#include "Bat.h"



void Bat::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + BAT_BBOX_WIDTH;
	bottom = y + BAT_BBOX_HEIGHT;
}

void Bat::LoadResources()
{
	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();
	LPANIMATION ani;
	Textures * textures = Textures::GetInstance();

	textures->Add(ID_TEX_BATL, L"Resource\\sprites\\Enemies\\BATL.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_BATR, L"Resource\\sprites\\Enemies\\BATR.png", D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 texBatL = textures->Get(ID_TEX_BATL);
	LPDIRECT3DTEXTURE9 texBatR = textures->Get(ID_TEX_BATR);

	sprites->Add(120011, 0, 0, 32, 32, texBatL);
	sprites->Add(120012, 32, 0, 64, 32, texBatL);
	sprites->Add(120013, 64, 0, 96, 32, texBatL);
	sprites->Add(120014, 96, 0, 128, 32, texBatL);

	sprites->Add(120001, 96, 0, 128, 32, texBatR);
	sprites->Add(120002, 64, 0, 96, 32, texBatR);
	sprites->Add(120003, 32, 0, 64, 32, texBatR);
	sprites->Add(120004, 0, 0, 32, 32, texBatR);

	ani = new Animation(100);  // idle
	ani->Add(120001);
	animations->Add(1201, ani);

	ani = new Animation(100);	// fly right
	ani->Add(120002);
	ani->Add(120003);
	ani->Add(120004);
	animations->Add(1202, ani);

	ani = new Animation(100);	// idle
	ani->Add(120012);
	ani->Add(120013);
	ani->Add(120014);
	animations->Add(1203, ani);

	AddAnimation(1201);
	AddAnimation(1202);
	AddAnimation(1203);

}

void Bat::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (hp > 0)
	{
		vy += GRAVITY;

		if (y >= defaultY)
			vy = -0.1;

		GameObject::Update(dt, coObjects);
		if (isRun)
		{
			x += dx;
			y += dy;
		}

	}
	else
		isEnable = false;
	
}

void Bat::Render()
{
	int ani;
	if (nx > 0)
		ani = BAT_ANI_FLY_RIGHT;
	else ani = BAT_ANI_FLY_LEFT;

	animations[ani]->Render(x, y);
	//RenderBoundingBox();
}

void Bat::SetState(int state)
{
	defaultY = y;
	GameObject::SetState(state);
	switch (state)
	{
	case BAT_STATE_IDLE:
		vx = 0;
		vy = 0;
		break;
	case BAT_STATE_FLY:
		if (nx > 0)
		{
			vx += BAT_WALK_SPEED;
			vy -= BAT_FLY_SPEED;
		}
		else
		{
			vx -= BAT_WALK_SPEED;
			vy -= BAT_FLY_SPEED;
		}
		break;
	}

}
