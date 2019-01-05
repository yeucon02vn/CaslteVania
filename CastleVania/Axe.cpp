#include "Axe.h"



Axe::Axe() : GameObject()
{
	
}

void Axe::LoadResources()
{
	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();
	LPANIMATION ani;
	Textures * textures = Textures::GetInstance();

	textures->Add(ID_TEX_AXE, L"Resource\\sprites\\Sub_weapons\\AXE_ACTION.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_AXE_L, L"Resource\\sprites\\Sub_weapons\\AXE_ACTIONL.png", D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 texAxe= textures->Get(ID_TEX_AXE);
	LPDIRECT3DTEXTURE9 texAxeL = textures->Get(ID_TEX_AXE_L);


	sprites->Add(51001, 0, 0, 30, 28, texAxe);
	sprites->Add(51002, 30, 0, 60, 28, texAxe);
	sprites->Add(51003, 60, 0, 90, 28, texAxe);
	sprites->Add(51004, 90, 0, 120, 28, texAxe);

	sprites->Add(51011, 0, 0, 30, 28, texAxeL);
	sprites->Add(51012, 30, 0, 60, 28, texAxeL);
	sprites->Add(51013, 60, 0, 90, 28, texAxeL);
	sprites->Add(51014, 90, 0, 120, 28, texAxeL);

	ani = new Animation(75);  // 
	ani->Add(51004);
	ani->Add(51003);
	ani->Add(51002);
	ani->Add(51001);
	animations->Add(511, ani);

	ani = new Animation(75);  // 
	ani->Add(51011);
	ani->Add(51012);
	ani->Add(51013);
	ani->Add(51014);
	animations->Add(512, ani);

	AddAnimation(511);
	AddAnimation(512);
}

void Axe::Render()
{
	if (nx > 0)
		animations[0]->Render(x, y);
	else
		animations[1]->Render(x, y);
}

void Axe::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (nx < 0) vx = -ITEM_AXE_SPEED;
	else vx = ITEM_AXE_SPEED;

	if (y <= preY)
	{
		isFalling = true;
	}

	if (isFalling == false)
		vy = -ITEM_AXE_JUMP;
	else
		vy += GRAVITY * 5;

	

	GameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	if (isEnable == true)
		CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];


			if (dynamic_cast<Boss *> (e->obj))
			{
				e->obj->SetState(BOSS_STATE_HURT);
				coEnemy = true;
			}

			else if (dynamic_cast<Enemy *> (e->obj))
			{
				e->obj->SetHP(2);
				coEnemy = true;
			}
			else
			{
				x += dx;
				y += dy;
			}
		}

	}
}
void Axe::setPositionAxe(float x, float y)
{
	x += 30;
	SetPosition(x, y);
	preY = y - 20;
	vy = -ITEM_AXE_JUMP;
	isFalling = false;
}


void Axe::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + AXE_BBOX_WIDTH;
	bottom = top + AXE_BBOX_HEIGHT;
}

