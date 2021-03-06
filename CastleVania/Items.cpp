#include "Items.h"
#include "Whip.h"

Items::Items() : GameObject()
{
	vy = ITEM_FALLING_SPEED;
	timeDelete = -1;
	AddAnimation(500);
	AddAnimation(501);
	AddAnimation(502);
	AddAnimation(504);
	AddAnimation(505);
	AddAnimation(506);
	AddAnimation(507);
	AddAnimation(508);
	AddAnimation(591);
	AddAnimation(592);
	AddAnimation(593);
	AddAnimation(594);
	AddAnimation(595);
}

void Items::LoadResources()
{
	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();
	LPANIMATION ani;
	Textures * textures = Textures::GetInstance();

	textures->Add(ID_TEX_BIG_HEART, BIG_HEART_SPRITE, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_SMALL_HEART, L"Resource\\sprites\\Items\\SMALL_HEART.png", D3DCOLOR_XRGB(255, 0, 255));

	textures->Add(ID_TEX_INVICIBILITY, L"Resource\\sprites\\Items\\INVICIBILITY_ITEM.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ROAST, L"Resource\\sprites\\Items\\ROAST.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_ROSARY, L"Resource\\sprites\\Items\\ROSARY.png", D3DCOLOR_XRGB(255, 0, 255));

	textures->Add(ID_TEX_DOUBLE_SHOT, L"Resource\\sprites\\Items\\DOUBLE_SHOT.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_TRIPLE_SHOT, L"Resource\\sprites\\Items\\TRIPLE_SHOT.png", D3DCOLOR_XRGB(255, 255, 255));

	textures->Add(ID_TEX_MORNING_STAR, MORNING_STAR_SPRITE, D3DCOLOR_XRGB(255, 255, 255));

	textures->Add(ID_TEX_KNIFE_L, KNIFE_L_SPRITE, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_KNIFE, KNIFE_SPRITE, D3DCOLOR_XRGB(255, 0, 255));

	textures->Add(ID_TEX_ITEM_AXE, L"Resource\\sprites\\Sub_weapons\\AXE.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_CROSS, L"Resource\\sprites\\Sub_weapons\\CROSS.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_HOLYWATER, L"Resource\\sprites\\Sub_weapons\\HOLY_WATER.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_STOP_WATCH, L"Resource\\sprites\\Sub_weapons\\STOP_WATCH.png", D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texBigHeart = textures->Get(ID_TEX_BIG_HEART);
	LPDIRECT3DTEXTURE9 texMorningStar = textures->Get(ID_TEX_MORNING_STAR);
	LPDIRECT3DTEXTURE9 texHeart = textures->Get(ID_TEX_SMALL_HEART);

	LPDIRECT3DTEXTURE9 texInvi = textures->Get(ID_TEX_INVICIBILITY);
	LPDIRECT3DTEXTURE9 texRoast = textures->Get(ID_TEX_ROAST);
	LPDIRECT3DTEXTURE9 texRosary = textures->Get(ID_TEX_ROSARY);

	LPDIRECT3DTEXTURE9 texDouble = textures->Get(ID_TEX_DOUBLE_SHOT);
	LPDIRECT3DTEXTURE9 texTriple = textures->Get(ID_TEX_TRIPLE_SHOT);
	
	LPDIRECT3DTEXTURE9 texKnife = textures->Get(ID_TEX_KNIFE);
	LPDIRECT3DTEXTURE9 texKnifeL = textures->Get(ID_TEX_KNIFE_L);
	LPDIRECT3DTEXTURE9 texAxe = textures->Get(ID_TEX_ITEM_AXE);
	LPDIRECT3DTEXTURE9 texCross = textures->Get(ID_TEX_ITEM_CROSS);
	LPDIRECT3DTEXTURE9 texHolyWater = textures->Get(ID_TEX_HOLYWATER);
	LPDIRECT3DTEXTURE9 texStopWatch = textures->Get(ID_TEX_STOP_WATCH);




	sprites->Add(50001, 0, 0, 24, 20, texBigHeart);
	sprites->Add(50002, 0, 0, 16, 16, texHeart);

	sprites->Add(50011, 0, 0, 32, 32, texMorningStar);

	sprites->Add(50021, 0, 0, 32, 18, texKnife);
	sprites->Add(50022, 0, 0, 32, 18, texKnifeL);
	sprites->Add(50031, 0, 0, 30, 28, texAxe);
	sprites->Add(50041, 0, 0, 30, 28, texCross);
	sprites->Add(50051, 0, 0, 32, 32, texHolyWater);
	sprites->Add(50061, 0, 0, 30, 32, texStopWatch);

	sprites->Add(50071, 0, 0, 33, 40, texInvi);
	sprites->Add(50072, 0, 0, 32, 26, texRoast);
	sprites->Add(50073, 0, 0, 32, 32, texRosary);
	sprites->Add(50074, 0, 0, 28, 28, texDouble);
	sprites->Add(50075, 0, 0, 28, 28, texTriple);

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

	ani = new Animation(100);  // small heart
	ani->Add(50002);
	animations->Add(504, ani);

	ani = new Animation(100);  // axe 
	ani->Add(50031);
	animations->Add(505, ani);

	ani = new Animation(100);  // cross 
	ani->Add(50041);
	animations->Add(506, ani);

	ani = new Animation(100);  //Holywatar 
	ani->Add(50051);
	animations->Add(507, ani);

	ani = new Animation(100);  // stop watch
	ani->Add(50061);
	animations->Add(508, ani);

	ani = new Animation(100); // invi
	ani->Add(50071);
	animations->Add(591, ani);

	ani = new Animation(100); // roast
	ani->Add(50072);
	animations->Add(592, ani);

	ani = new Animation(100); // rosasy
	ani->Add(50073);
	animations->Add(593, ani);

	ani = new Animation(100); // double
	ani->Add(50074);
	animations->Add(594, ani);

	ani = new Animation(100); // triple
	ani->Add(50075);
	animations->Add(595, ani);
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
		
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			// collision of Simon and Candle -> do nothing -> update x;
			if (dynamic_cast<Ground *>(e->obj))
			{
				y += min_ty*dy + ny*0.4f;

				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
			}
			else
			{
				if (e->nx != 0)
					x += dx;
				if (e->ny != 0)
					y += dy;
			}
		}

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
			state = ITEM_ANI_SMALL_HERT;
		}
	}
	else if (percent < 70)
	{
		state = ITEM_ANI_BIG_HERT;
	}
	else if (percent < 80)
	{
		state = ITEM_ANI_ROAST;
	}
	else if (percent < 85)
	{
		state = ITEM_ANI_ROSASY;
	}
	else if (percent < 90)
	{
		state = ITEM_ANI_DOUBLE;
	}
	else if (percent < 95)
	{
		state = ITEM_ANI_TRIPLE;
	}
}

void Items::RandomSubWeapon()
{
	int percent = rand() % 100;
	if (percent < 40)
	{
		state = ITEM_ANI_KNIFE;
	}
	else if (percent < 60)
	{
		state = ITEM_ANI_AXE;
	}
	else if (percent < 75)
	{
		state = ITEM_ANI_CROSS;
	}
	else if ( percent < 85)
	{
		state = ITEM_ANI_HOLYWATER;
	}
	else
	{
		state = ITEM_ANI_STOPWATCH;
	}
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
	case ITEM_ANI_SMALL_HERT:
		right = x + SMALL_HEART_BBOX_WIDTH;
		bottom = y + SMALL_HEART_BBOX_HEIGHT;
		break;
	case ITEM_ANI_WHIP:
		right = x + MORNING_STAR_BBOX_WIDTH;
		bottom = y + MORNING_STAR_BBOX_HEIGHT;
		break;
	case ITEM_ANI_KNIFE:
		right = x + KNIFE_BBOX_WIDTH;
		bottom = y + KNIFE_BBOX_HEIGHT;
		break;
	case ITEM_ANI_AXE:
		right = x + AXE_BBOX_WIDTH;
		bottom = y + AXE_BBOX_HEIGHT;
		break;
	case ITEM_ANI_CROSS:
		right = x + CROSS_BBOX_WIDTH;
		bottom = y + CROSS_BBOX_HEIGHT;
		break;
	case ITEM_ANI_HOLYWATER:
		right = x + HOLYWATER_BBOX_WIDTH;
		bottom = y + HOLYWATER_BBOX_HEIGHT ;
		break;
	case ITEM_ANI_STOPWATCH:
		right = x + STOPWATCH_BBOX_WIDTH;
		bottom = y + STOPWATCH_BBOX_HEIGHT;
		break;
	case ITEM_ANI_INVI:
		right = x + INVI_BBOX_WIDTH;
		bottom = y + INVI_BBOX_HEIGHT;
		break;
	case ITEM_ANI_ROAST:
		right = x +  ROAST_BBOX_WIDTH;
		bottom = y + ROAST_BBOX_HEIGHT;
		break;
	case ITEM_ANI_ROSASY:
		right = x + ROSASY_BBOX_WIDTH;
		bottom = y + ROSASY_BBOX_HEIGHT;
		break;
	case ITEM_ANI_DOUBLE:
		right = x +  DOUBLE_BBOX_WIDTH;
		bottom = y + DOUBLE_BBOX_HEIGHT;
		break;
	case ITEM_ANI_TRIPLE:
		right = x +  TRIPLE_BBOX_WIDTH;
		bottom = y + TRIPLE_BBOX_HEIGHT;
		break;
	default:
		break;
	}
}
