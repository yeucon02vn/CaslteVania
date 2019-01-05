#include "Zombie.h"



void Zombie::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + ZOMBIE_BBOX_WIDTH;
	bottom = y + ZOMBIE_BBOX_HEIGHT;
}

void Zombie::LoadResources()
{
	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();
	LPANIMATION ani;
	Textures * textures = Textures::GetInstance();

	textures->Add(ID_TEX_ZOMBIEL, L"Resource\\sprites\\Enemies\\ZOMBIEL.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ZOMBIER, L"Resource\\sprites\\Enemies\\ZOMBIER.png", D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 texZombieL = textures->Get(ID_TEX_ZOMBIEL);
	LPDIRECT3DTEXTURE9 texZombieR = textures->Get(ID_TEX_ZOMBIER);

	sprites->Add(130011, 0, 0, 34, 64, texZombieL);
	sprites->Add(130012, 34, 0, 68, 64, texZombieL);


	sprites->Add(130001, 34, 0, 68, 64, texZombieR);
	sprites->Add(130002, 0, 0, 34, 64, texZombieR);


	ani = new Animation(100);  // idle
	ani->Add(130001);
	ani->Add(130002);
	animations->Add(1301, ani);

	ani = new Animation(100);	// idle
	ani->Add(130011);
	ani->Add(130012);
	animations->Add(1302, ani);

	AddAnimation(1301);
	AddAnimation(1302);

}

void Zombie::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (hp > 0)
	{
		if (isRun)
		{
			if (nx > 0)
			{
				vx = ZOMBIE_WALK_SPEED;
				vy += 0;
			}
			else
			{
				vx = -ZOMBIE_WALK_SPEED;
				vy -= 0;
			}
		}
		else
		{
			vx = 0;
		}
			vy += GRAVITY;

			GameObject::Update(dt);

			//for (UINT i = 0; i < coObjects->size(); i++)
			//{
			//	LPGAMEOBJECT e = coObjects->at(i);
			//	if (dynamic_cast<Zombie *>(e))
			//	{
			//		coObjects->erase(coObjects->begin() +i);
			//	}
			//}

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

					// collision of Simon and Candle -> do nothing -> update x;
					if (dynamic_cast<Ground *>(e->obj))
					{
						y += min_ty*dy + ny*0.4f;

						//if (nx != 0) vx = 0;
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
			for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		}
	else
		isEnable = false;
}
void Zombie::Render()
{
	int ani;
	if (nx > 0)
		ani = ZOMBIE_ANI_WALK_RIGHT;
	else ani = ZOMBIE_ANI_WALK_LEFT;

	animations[ani]->Render(x, y);
	//RenderBoundingBox();
}

void Zombie::SetState(int state)
{
	GameObject::SetState(state);
	switch (state)
	{

	case ZOMBIE_STATE_WALK:
		if (nx > 0)
		{
			vx += ZOMBIE_WALK_SPEED;
			vy += 0;
		}
		else
		{
			vx -= ZOMBIE_WALK_SPEED;
			vy -= 0;
		}
		break;
	}

}
