#include "Cross.h"



Cross::Cross() : GameObject()
{

}

void Cross::LoadResources()
{
	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();
	LPANIMATION ani;
	Textures * textures = Textures::GetInstance();

	textures->Add(ID_TEX_CROSS, L"Resource\\sprites\\Sub_weapons\\CROSS_ACTION.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_CROSS_L, L"Resource\\sprites\\Sub_weapons\\CROSS_ACTIONL.png", D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 texCross = textures->Get(ID_TEX_CROSS);
	LPDIRECT3DTEXTURE9 texCrossL = textures->Get(ID_TEX_CROSS_L);


	sprites->Add(52001, 0, 0, 28, 28, texCross);
	sprites->Add(52002, 28, 0, 56, 28, texCross);
	sprites->Add(52003, 56, 0, 84, 28, texCross);

	sprites->Add(52011, 0, 0, 28, 28, texCrossL);
	sprites->Add(52012, 28, 0, 56, 28, texCrossL);
	sprites->Add(52013, 56, 0, 84, 28, texCrossL);

	ani = new Animation(100);  // 
	ani->Add(52001);
	ani->Add(52002);
	ani->Add(52003);
	animations->Add(521, ani);

	ani = new Animation(100);  // 
	ani->Add(52013);
	ani->Add(52012);
	ani->Add(52011);
	animations->Add(522, ani);

	AddAnimation(521);
	AddAnimation(522);
}

void Cross::Render()
{
	if (nx > 0)
		animations[0]->Render(x, y);
	else
		animations[1]->Render(x, y);
}

void Cross::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (isReverse == true)
	{
		if (nx > 0) vx = -ITEM_CROSS_SPEED;
		else vx = ITEM_CROSS_SPEED ;
	}
	else
	{
		if (nx < 0) vx = -ITEM_CROSS_SPEED ;
		else vx = ITEM_CROSS_SPEED;
	}
	
	if (nx > 0)
	{
		if (x >= preX)
		{
			isReverse = true;
		}
	}
	else
	{
		if (x <= preX)
		{
			isReverse = true;
		}
	}
	

	GameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	if (isEnable == true)
		CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
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
			}
		}

	}
}
void Cross::setPositionCross(float x, float y)
{
	if (nx > 0)
	{
		x += 50;
		preX = x + 150;
	}
	else
	{
		preX = x - 150;
		x -= 20;
	}
		

	y += 15;
	if (isSit == true)
		y += 15.0f;
	SetPosition(x, y);
	isReverse = false;
}


void Cross::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + CROSS_BBOX_WIDTH;
	bottom = top + CROSS_BBOX_HEIGHT;
}

