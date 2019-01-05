#include "Panther.h"



void Panther::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x ;
	top = y + 10;
	right = x + PANTHER_BBOX_WIDTH;
	bottom = y + PANTHER_BBOX_HEIGHT;
}

void Panther::LoadResources()
{
	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();
	LPANIMATION ani;
	Textures * textures = Textures::GetInstance();

	textures->Add(ID_TEX_PANTHERL, L"Resource\\sprites\\Enemies\\PANTHERL.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_PANTHERR, L"Resource\\sprites\\Enemies\\PANTHERR.png", D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 texPantherL = textures->Get(ID_TEX_PANTHERL);
	LPDIRECT3DTEXTURE9 texPantherR = textures->Get(ID_TEX_PANTHERR);

	sprites->Add(140011, 0, 0, 64, 32, texPantherL);
	sprites->Add(140012, 64, 0, 128, 32, texPantherL);
	sprites->Add(140013, 128, 0, 196, 32, texPantherL);
	sprites->Add(140014, 196, 0, 256, 32, texPantherL);

	sprites->Add(140001, 196, 0, 256, 32, texPantherR);
	sprites->Add(140002, 128, 0, 196, 32, texPantherR);
	sprites->Add(140003, 64, 0, 128, 32, texPantherR);
	sprites->Add(140004, 0, 0, 64, 32, texPantherR);


	ani = new Animation(100);  // idle right
	ani->Add(140001);
	animations->Add(1401, ani);

	ani = new Animation(100);  // idle left
	ani->Add(140011);
	animations->Add(1402, ani);


	ani = new Animation(100);	// walk right
	ani->Add(140002);
	ani->Add(140003);
	ani->Add(140004);
	animations->Add(1403, ani);

	ani = new Animation(100);	// walk left
	ani->Add(140012);
	ani->Add(140013);
	ani->Add(140014);
	animations->Add(1404, ani);

	AddAnimation(1401);
	AddAnimation(1402);
	AddAnimation(1403);
	AddAnimation(1404);

}

void Panther::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (hp > 0)
	{
		if (isRun)
		{
			if (nx > 0)
			{
				vx = PANTHER_WALK_SPEED;
			}
			else
			{
				vx = -PANTHER_WALK_SPEED;
			}
		}
		else
		{
			vx = 0;
		}
			if (isJump == false)
				vy += GRAVITY;
			else
				vy += PANTHER_JUMP_DEFLECT;

			GameObject::Update(dt, coObjects);

			vector<LPCOLLISIONEVENT> coEvents;
			vector<LPCOLLISIONEVENT> coEventsResult;

			coEvents.clear();

			CalcPotentialCollisions(coObjects, coEvents);


			if (coEvents.size() == 0 && isRun && isGround)
			{
				if (state != 1 && y >= 290)
				{
					if (isCheck == false)
					{
						SetState(PANTHER_STATE_JUMP);
					}
				}
				if (state == 1 && y >= 225)
				{
					if (isCheck == false)
					{
						SetState(PANTHER_STATE_JUMP);
					}
				}
			}

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

						if (isJump == true && isGround == false)
						{
							isJump = false;
							this->nx = -this->nx;
						}
						isGround = true;
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

			for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		}
	else
	{
		isEnable = false;
	}

}

void Panther::Render()
{
	int ani;
	if (isRun)
	{
		if (nx > 0)
			ani = PANTHER_ANI_WALK_RIGHT;
		else ani = PANTHER_ANI_WALK_LEFT;
	}
	else
	{
		if (nx > 0)
			ani = PANTHER_ANI_IDLE_RIGHT;
		else
			ani = PANTHER_ANI_IDLE_LEFT;
	}
	if (isJump == true && isGround == false)
	{
		animations[ani]->setCurrentFrame(animations[ani]->getLastFrame());
		animations[ani]->Draw(x,y);
	}
	else
		animations[ani]->Render(x, y);
	//RenderBoundingBox();
}

void Panther::SetState(int state)
{
	GameObject::SetState(state);
	switch (state)
	{
	case PANTHER_STATE_IDLE:
		vx = 0;
		vy = 0;
		break;
	case PANTHER_STATE_JUMP:
		vy -= PANTHER_JUMP_SPEED;
		isCheck = true;
		isJump = true;
		isGround = false;
		break;
	}
	
}

