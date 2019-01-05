#include "Merman.h"



void Merman::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + MERMAN_BBOX_WIDTH;
	bottom = y + MERMAN_BBOX_HEIGHT;
}

void Merman::LoadResources()
{
	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();
	LPANIMATION ani;
	Textures * textures = Textures::GetInstance();

	textures->Add(ID_TEX_MERMANL, L"Resource\\sprites\\Enemies\\MERMANL.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_MERMANR, L"Resource\\sprites\\Enemies\\MERMANR.png", D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 texMermanL = textures->Get(ID_TEX_MERMANL);
	LPDIRECT3DTEXTURE9 texMermanR = textures->Get(ID_TEX_MERMANR);

	sprites->Add(160001, 0, 0, 32, 64, texMermanR);
	sprites->Add(160002, 32, 0, 64, 64, texMermanR);
	sprites->Add(160003, 64, 0, 96, 64, texMermanR);

	sprites->Add(161001, 64, 0, 96, 64, texMermanL);
	sprites->Add(161002, 32, 0, 64, 64, texMermanL);
	sprites->Add(161003, 0, 0, 32, 64, texMermanL);


	ani = new Animation(100);  // idle
	ani->Add(160001);
	animations->Add(1601, ani);

	ani = new Animation(300);	// right
	ani->Add(160001);
	ani->Add(160002);
	ani->Add(160003);
	animations->Add(1602, ani);

	ani = new Animation(300);	// left
	ani->Add(161001);
	ani->Add(161002);
	ani->Add(161003);
	animations->Add(1603, ani);

	AddAnimation(1601);
	AddAnimation(1602);
	AddAnimation(1603);
	grid = grid->GetInstance();

}

void Merman::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (hp > 0)
	{

			if (isRun && isGround)
			{
				if (nx > 0)
					vx = MERMAN_WALK_SPEED/4;
				else
					vx = -MERMAN_WALK_SPEED/4;
				vy += GRAVITY;
				isIdle = false;

			}
			else if (isRun && !isGround && isFalling)
			{
				vy += GRAVITY *4;
				isIdle = true;
				isCreateEffect = false;
			}
			else if(isRun)
			{
				vy = -MERMAN_JUMP_SPEED;
				if(y <= 700)
					isFalling = true;
				isIdle = true;

			}
		if ( y <=890 && y >= 872 && !isCreateEffect && isRun)
		{
			effect = new EffectDead();
			effect->LoadResources();
			effect->SetPosition(x, y);
			effect->state = 2;
			effect->isEffect = false;
			grid->AddObject(effect);
			isCreateEffect = true;
		}
		if (y > 1000)
		{
			isEnable = false;
		}
		if ((animations[1]->getLastFrame() == animations[1]->getCurrentFrame() || animations[2]->getLastFrame() == animations[2]->getCurrentFrame()) && isRun && isGround  && !isFire )
		{
			vx = 0;
			bullet = new Bullets();
			bullet->LoadResources();
			bullet->setPositionBullet(x, y);
			bullet->setNx(nx);
	
			grid->AddObject(bullet);
			isFire = true;
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

				// collision of Simon and Candle -> do nothing -> update x;
				if (dynamic_cast<Ground *>(e->obj))
				{
					if (isFalling == true && !isGround)
					{
						isGround = true;
					}
					if (ny > 0)
					{
						if (e->nx != 0)
							x += dx;
						if (e->ny != 0)
							y += dy;
						
					}
					else
					{
						y += min_ty*dy + ny*0.4f;

						if (nx != 0) vx = 0;
						if (ny != 0) vy = 0;
					}
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

void Merman::Render()
{
	if(isIdle)
		ani = MERMAN_ANI_IDLE;
	else if(isRun)
		if (nx > 0)
			ani = MERMAN_ANI_WALK_RIGHT;
		else ani = MERMAN_ANI_WALK_LEFT;

	animations[ani]->Render(x, y);
	//RenderBoundingBox();
}

void Merman::SetState(int state)
{
	GameObject::SetState(state);
}
