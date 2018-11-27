#include "Items.h"
#include "Whip.h"

Items::Items() : GameObject()
{
	vy = ITEM_FALLING_SPEED;
	timeDelete = -1;
	AddAnimation(500);
	AddAnimation(501);
	AddAnimation(502);
}

void Items::LoadResources()
{
	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();
	LPANIMATION ani;
	Textures * textures = Textures::GetInstance();

	textures->Add(ID_TEX_BIG_HEART, BIG_HEART_SPRITE, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_KNIFE, KNIFE_SPRITE, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_MORNING_STAR, MORNING_STAR_SPRITE, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_KNIFE_L, KNIFE_L_SPRITE, D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 texBigHeart = textures->Get(ID_TEX_BIG_HEART);
	LPDIRECT3DTEXTURE9 texMorningStar = textures->Get(ID_TEX_MORNING_STAR);
	LPDIRECT3DTEXTURE9 texKnife = textures->Get(ID_TEX_KNIFE);
	LPDIRECT3DTEXTURE9 texKnifeL = textures->Get(ID_TEX_KNIFE_L);

	sprites->Add(50001, 0, 0, 24, 20, texBigHeart);
	sprites->Add(50011, 0, 0, 32, 32, texMorningStar);
	sprites->Add(50021, 0, 0, 32, 18, texKnife);
	sprites->Add(50022, 0, 0, 32, 18, texKnifeL);


	ani = new Animation(100);  // big heart
	ani->Add(50001);
	animations->Add(500, ani);

	ani = new Animation(100);	// MorningStar
	ani->Add(50011);
	animations->Add(501, ani);

	ani = new Animation(100);  // Knife
	ani->Add(50021);
	animations->Add(502, ani);
	
	ani = new Animation(100);  // Knife_L
	ani->Add(50022);
	animations->Add(503, ani);

}

void Items::Render()
{
	animations[state]->Render(x, y);
}

void Items::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects )
{

	if (timeDelete == -1)
	{
		timeDelete = GetTickCount();
	}
	else
	{
		DWORD now = GetTickCount();

		if (now - timeDelete > ITEM_TIME_DESTROYED)
		{
			isEnable = false;
			return;
		}
	}


	GameObject::Update(dt);

	// Check collision between item and ground (falling on ground)
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed


	// No collision occured, proceed normally
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
		//x += min_tx*dx + nx*0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty*dy + ny*0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;



	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

int Items::Random()
{
	int percent = rand() % 100; // random theo tỉ lệ
	if (percent < 75)
		RandomItem();
	else
		RandomSubWeapon();
	return state;
}

void Items::RandomItem()
{
	int percent = rand() % 100; // random theo tỉ lệ

	if (percent < 60)
	{
		if(isLv2 == false)
		{
			state = ITEM_ANI_WHIP;
		}
		else
		{
			state = ITEM_ANI_BIG_HERT;
		}
	}
	else 
	{
		state = ITEM_ANI_BIG_HERT;
	}
}

void Items::RandomSubWeapon()
{
	//int percent = rand() % 100;
	// sẽ cho phần trăm cho từng cái ,hiện do có 1 cái nên ko cần;
	state = ITEM_ANI_KNIFE;
}

void Items::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;

switch (state)
	{
	case ITEM_ANI_BIG_HERT:
		right = x + BIG_HEART_BBOX_WIDTH;
		bottom = y + BIG_HEART_BBOX_HEIGHT;
		break;
	case ITEM_ANI_WHIP:
		right = x + MORNING_STAR_BBOX_WIDTH;
		bottom = y + MORNING_STAR_BBOX_HEIGHT;
		break;
	case ITEM_ANI_KNIFE:
		right = x + KNIFE_BBOX_WIDTH;
		bottom = y + KNIFE_BBOX_HEIGHT;
		break;
	default:
		break;
	}
}
