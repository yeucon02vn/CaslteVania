#include "HolyWater.h"



HolyWater::HolyWater() : GameObject()
{

}

void HolyWater::LoadResources()
{
	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();
	LPANIMATION ani;
	Textures * textures = Textures::GetInstance();

	textures->Add(ID_TEX_HOLYWATER, L"Resource\\sprites\\Sub_weapons\\HOLY_WATER_ACTION.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_HOLYWATER_L, L"Resource\\sprites\\Sub_weapons\\HOLY_WATER_ACTIONL.png", D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 texHolyWater = textures->Get(ID_TEX_HOLYWATER);
	LPDIRECT3DTEXTURE9 texHolyWaterL = textures->Get(ID_TEX_HOLYWATER_L);


	sprites->Add(53001, 0, 0, 32, 26, texHolyWater);
	sprites->Add(53002, 32, 0, 64, 26, texHolyWater);
	sprites->Add(53003, 64, 0, 96, 26, texHolyWater);


	sprites->Add(53011, 0, 0, 32, 26, texHolyWaterL);
	sprites->Add(53012, 32, 0, 64, 26, texHolyWaterL);
	sprites->Add(53013, 64, 0, 96, 26, texHolyWaterL);


	ani = new Animation(75);  // bình
	ani->Add(53001);
	animations->Add(531, ani);

	ani = new Animation(75);  // lừa khi va chạm đất phải
	ani->Add(53002);
	ani->Add(53003);
	animations->Add(532, ani);

	ani = new Animation(75);  //  bình trái
	ani->Add(53013);
	animations->Add(533, ani);

	ani = new Animation(75);  //  lửa trái
	ani->Add(53012);
	ani->Add(53011);
	animations->Add(534, ani);

	AddAnimation(531);
	AddAnimation(532);
	AddAnimation(533);
	AddAnimation(534);
}

void HolyWater::Render()
{
	if (!isGround)
	{
		if (nx > 0)
			animations[0]->Render(x, y);
		else
			animations[2]->Render(x, y);
	}
	else
	{
		if (nx > 0)
			animations[1]->Render(x, y);
		else
			animations[3]->Render(x, y);
	}
}

void HolyWater::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (!isGround)
	{
		if (nx < 0) vx = -ITEM_HOLYWATER_SPEED;
		else vx = ITEM_HOLYWATER_SPEED;
	}
	else
		vx = 0;
	vy += GRAVITY * 3 ;

	if (isGround)
	{
		if (start == false)
		{
			start = true;
			startTime += GetTickCount();

		}
		else
		{

			if (GetTickCount() - startTime > 750)
			{
				start = false;
				startTime = 0;
				isGround = false;
				noRender = true;
			}
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
			}

			else if (dynamic_cast<Enemy *> (e->obj))
			{
				e->obj->SetHP(2);
			}
			else if (dynamic_cast<Ground *> (e->obj))
			{
				isGround = true;
				y += min_ty*dy + ny*0.4f;
				x += min_tx*dx + nx*0.4f;
				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
			}
			else
			{
				x += dx;
				y += dy;
			}
		}

	}
}
void HolyWater::setPositionHolyWater(float x, float y)
{
	x += 30;
	SetPosition(x, y);
	vy = -ITEM_HOLYWATER_JUMP;
	isGround = false;
	noRender = false;
}


void HolyWater::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + HOLYWATER_BBOX_WIDTH;
	bottom = top + HOLYWATER_BBOX_HEIGHT;
}

