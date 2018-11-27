#include <algorithm>
#include "debug.h"
#include "Simon.h"
#include "Game.h"

Simon::Simon() : GameObject()
{
	whip = new Whip();
	whip->LoadResources();
}


void Simon::LoadResources()
{
	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();
	Textures * textures = Textures::GetInstance();

	textures->Add(ID_TEX_SIMONR, SIMON_R_SPRITE, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_SIMONL, SIMON_L_SPRITE, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_BBOX, BBOX_SPRITE, D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texSimonL = textures->Get(ID_TEX_SIMONL);
	LPDIRECT3DTEXTURE9 texSimonR = textures->Get(ID_TEX_SIMONR);

	//right
	sprites->Add(10001, 240, 0, 300, 66, texSimonR);		// walk
	sprites->Add(10002, 300, 0, 360, 66, texSimonR);
	sprites->Add(10003, 360, 0, 420, 66, texSimonR);
	sprites->Add(10004, 420, 0, 480, 66, texSimonR);		// idle 

	sprites->Add(10011, 180, 0, 240, 66, texSimonR);     // sit

	sprites->Add(10021, 120, 0, 180, 66, texSimonR);    // atk
	sprites->Add(10022, 60, 0, 120, 66, texSimonR);
	sprites->Add(10023, 0, 0, 60, 66, texSimonR);

	sprites->Add(10031, 0, 66, 60, 132, texSimonR);    // sit atk
	sprites->Add(10032, 420, 132, 480, 198, texSimonR);
	sprites->Add(10033, 360, 132, 420, 198, texSimonR);
	sprites->Add(10041, 120, 198, 180, 264, texSimonR); // jump

	//sprites->Add(10099, 180, 198, 240, 264, texSimonR);		// die 

															// left
	sprites->Add(11001, 180, 0, 240, 66, texSimonL);// walk 
	sprites->Add(11002, 120, 0, 180, 66, texSimonL); // idle
	sprites->Add(11003, 60, 0, 120, 66, texSimonL);
	sprites->Add(11004, 0, 0, 60, 66, texSimonL);		

	sprites->Add(11011, 240, 0, 300, 66, texSimonL); // sit

	sprites->Add(11021, 300, 0, 360, 66, texSimonL);		// atk
	sprites->Add(11022, 360, 0, 420, 66, texSimonL);
	sprites->Add(11023, 420, 0, 480, 66, texSimonL);

	sprites->Add(11031, 420, 66, 480, 132, texSimonL); // sit_atk
	sprites->Add(11032, 0, 132, 60, 198, texSimonL);
	sprites->Add(11033, 60, 132, 120, 198, texSimonL);

	sprites->Add(11041, 300, 198, 360, 264, texSimonL); // jump


	//sprites->Add(11099, 240, 198, 300, 264, texSimonL); // die

	//sprites->Add(11000, 0, 0, 0, 0, texSimonL);
	LPANIMATION ani;
	ani = new Animation(100);	// idle right
	ani->Add(10002);
	animations->Add(100, ani);

	ani = new Animation(100);	// idle left
	ani->Add(11002);
	animations->Add(101, ani);

	ani = new Animation(100);	// walk right
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	ani->Add(10004);
	animations->Add(102, ani);

	ani = new Animation(100);	// // walk left
	ani->Add(11001);
	ani->Add(11002);
	ani->Add(11003);
	ani->Add(11004);
	animations->Add(103, ani);

	ani = new Animation(100); // sit right
	ani->Add(10011);
	animations->Add(104, ani);

	ani = new Animation(100); // sit left
	ani->Add(11011);
	animations->Add(105, ani);


	ani = new Animation(100); // atk right
	ani->Add(10021);
	ani->Add(10022);
	ani->Add(10023);
	animations->Add(106, ani);


	ani = new Animation(100); // atk left
	ani->Add(11021);
	ani->Add(11022);
	ani->Add(11023);
	animations->Add(107, ani);


	ani = new Animation(100); // sit atk right
	ani->Add(10031);
	ani->Add(10032);
	ani->Add(10033);
	animations->Add(108, ani);


	ani = new Animation(100); // sit atk left
	ani->Add(11031);
	ani->Add(11032);
	ani->Add(11033);
	animations->Add(109, ani);


	ani = new Animation(100);
	ani->Add(10041);
	animations->Add(110, ani);

	ani = new Animation(100);
	ani->Add(11041);
	animations->Add(111, ani);

	AddAnimation(100);		// idle right
	AddAnimation(101);		// idle left
	AddAnimation(102);		// walk right
	AddAnimation(103);		// walk left
	AddAnimation(104);		// sit right
	AddAnimation(105);		// sit  left
	AddAnimation(106);		//atk right	
	AddAnimation(107);		//atk left	
	AddAnimation(108);		// sit atk right
	AddAnimation(109);		// sit atk left
	AddAnimation(110);		// jump right
	AddAnimation(111);		// jump left;


}


void Simon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	
	GameObject::Update(dt);
	if (vy == 0 && isJumping == true)
	{
		isJumping = false;
		isGround = true;
	}
	// Simple fall down
	vy += GRAVITY*dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (isUseItem == true && HaveWeapon == true)
	{
		knife->setNx(nx);
		knife->Update(dt+ 50, coObjects);
	}
	
	if(this->checkFight())
	{
		if (startFight == false)
		{
			startFight = true;
			fightTime += GetTickCount();
			
		}
		else
		{
			float remain =  GetTickCount() - fightTime;

			if ( remain > SIMON_ATTACK_TIME)
			{		
				startFight = false;
				remain = 0;
				fightTime = 0;
				if(isSiting == true)
					this->SetState(SIMON_STATE_SIT);
				else 
					this->SetState(SIMON_STATE_IDLE);
				reset();
				whip->reset();
			}
		}
		
	}

	//action == SIMON_ANI_ATK_RIGHT || action == SIMON_ANI_ATK_LEFT || action== SIMON_ANI_S_ATK_RIGHT || action == SIMON_ANI_S_ATK_LEFT
	if ((isFighting && isSiting && !isUseItem) || (isFighting && !isSiting && !isUseItem))
	{
		whip->setNx(nx);
		whip->SetWhipPosition(x,y, isSiting);


 		if (animations[stateAtk]->getCurrentFrame() == animations[stateAtk]->getLastFrame()) // chỉ xét va chạm khi render tới sprite cuối cùng của roi
		{
			for (UINT i = 0; i < coObjects->size(); i++)
			{
				LPGAMEOBJECT e = coObjects->at(i);
				if (dynamic_cast<lCandle *>(e))
				{
					float left, top, right, bottom;
					e->GetBoundingBox(left, top, right, bottom);
					if (whip->CheckCollision(left, top, right, bottom) == true) // va chạm giữa roi và nến
					{
						DebugOut(L"VA CHAM");
						e->isEnable = false;
					}
				}
			}
		}
	}
	// turn off collision when die 
	if(state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

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

		

		

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			// collision of Simon and Candle -> do nothing -> update x;
			if (dynamic_cast<lCandle *>(e->obj))
			{
				if (e->nx != 0)
					x += dx;
				if (e->ny != 0)
					y += dy;
			}
			else if (dynamic_cast<Items *>(e->obj))
			{
				if (e->nx != 0)
					x += dx;
				if (e->ny != 0)
					y += dy;
				e->obj->isEnable = false;

				if (e->obj->GetState() == ITEM_ANI_WHIP)  
				{
					
					//vx = 0;
					
					if (whip->getType() == WHIP_NORMAL) whip->setType(WHIP_LV1);
					else if (whip->getType() == WHIP_LV1)
					{
						whip->setType(WHIP_LV2);
					}
				}
				if (e->obj->GetState() == ITEM_ANI_KNIFE)
				{
					knife = new Knife();
					HaveWeapon = true;
				}
			}
			else
			{
				x += min_tx*dx + nx*0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
				y += min_ty*dy + ny*0.4f;

				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
			}
		}

	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Simon::Render()
{
	if (state == SIMON_STATE_DIE)
		action = SIMON_ANI_DIE;
	else if (!isFighting && isGround)
	{
		if ((vx == 0 && isSiting == true))
		{
			if (nx > 0)
				action = SIMON_ANI_SIT_RIGHT;
			else
				action = SIMON_ANI_SIT_LEFT;
		}
		else if (vx != 0 && isSiting == false)
		{
			if (nx > 0)
				action = SIMON_ANI_WALKING_RIGHT;
			else
				action = SIMON_ANI_WALKING_LEFT;
		}
		else
		{
				if (nx > 0 )
					action = SIMON_ANI_IDLE_RIGHT;
				else
					action = SIMON_ANI_IDLE_LEFT;
		}
	}
	else if (!isFighting && isJumping)
	{
		if (nx > 0)
			action = SIMON_ANI_JUMP_RIGHT;
		else
			action = SIMON_ANI_JUMP_LEFT;
	}
	else if (isFighting && !isSiting)
	{
		if (nx > 0)
		{
		action = SIMON_ANI_ATK_RIGHT;
		stateAtk = SIMON_ANI_ATK_RIGHT;
		}
		else
		{
			action = SIMON_ANI_ATK_LEFT;
			stateAtk = SIMON_ANI_ATK_LEFT;
		}
		if (HaveWeapon == true && isUseItem == true)
			knife->Render();
		else
			whip->Render();
	}
	else if (isFighting && isSiting)
	{
		if (nx > 0)
		{
		action = SIMON_ANI_S_ATK_RIGHT;
		stateAtk = SIMON_ANI_S_ATK_RIGHT;
	}
		else
		{
			action = SIMON_ANI_S_ATK_LEFT;
			stateAtk = SIMON_ANI_S_ATK_LEFT;
		}
		whip->Render();
	}

	
	int alpha = 255;
	if (untouchable) alpha = 128;
	animations[action]->Render(x, y, alpha);
}

void Simon::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case SIMON_STATE_WALK:
		isSiting = false;
		isFighting = false;
		isJumping = false;
		isGround = true;
		isUseItem = false;
		if(nx >0)
			vx = SIMON_WALKING_SPEED;
		else
			vx = -SIMON_WALKING_SPEED;

		break;
	case SIMON_STATE_JUMP:
		isFighting = false;
		isJumping = true;
		isSiting = false;
		isGround = false;
		isUseItem = false;
		vy = -SIMON_JUMP_SPEED_Y;
		break;
	case SIMON_STATE_IDLE:
		isFighting = false;
		isJumping = false;
		isSiting = false;
		isGround = true;
		isUseItem = false;
		vx = 0;
		break;
	case SIMON_STATE_DIE:
		vy = -SIMON_DIE_DEFLECT_SPEED;
		break;
	case SIMON_STATE_SIT:
		isFighting = false;
		isJumping = false;
		isSiting = true;
		isGround = true;
		isUseItem = false;
		vx = 0;
		break;
	case SIMON_STATE_ATK:
		isFighting = true;
		isJumping = false;
		isSiting = false;
		isGround = true;
		isUseItem = false;
		break;
	case SIMON_STATE_S_ATK:
		isFighting = true;
		isJumping = false;
		isSiting = true;
		isGround = true;
		isUseItem = false;
		break;
	case SIMON_STATE_USE_ITEM:
		isFighting = true;
		isJumping = false;
		isSiting = false;
		isGround = true;
		isUseItem = true;
		vx = 0;
		knife->setPositionKnife(x, y);
		break;
	}
}


void Simon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x + 12;
	top = y;
	right = x + SIMON_BBOX_WIDTH;
	bottom = y + SIMON_BBOX_HEIGHT;

}

void Simon::reset()
{
	animations[action]->setCurrentFrame(-1);
}
