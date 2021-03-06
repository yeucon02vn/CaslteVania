#include <algorithm>
#include "debug.h"
#include "Simon.h"
#include "Game.h"

Simon::Simon() : GameObject()
{
	whip = new Whip();
	whip->LoadResources();
	hp = 16;
	heart = 5;
	life = 3;
	dame = 2;
	stateAtk = 6;
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

	sprites->Add(10051, 240, 198, 300, 264, texSimonR);
	sprites->Add(10052, 300, 198, 360, 264, texSimonR);
	sprites->Add(10053, 360, 198, 420, 264, texSimonR);
	sprites->Add(10054, 420, 198, 480, 264, texSimonR); // nhấp nháy right
	

	sprites->Add(10061, 120, 66, 180, 132, texSimonR);
	sprites->Add(10062, 180, 66, 240, 132, texSimonR);
	sprites->Add(10063, 240, 66, 300, 132, texSimonR);
	sprites->Add(10064, 300, 66, 360, 132, texSimonR);
	
	sprites->Add(10071, 0, 132, 60, 198, texSimonR); // đánh trên cầu thang phải
	sprites->Add(10072, 60, 132, 120, 198, texSimonR);
	sprites->Add(10073, 120, 132, 180, 198, texSimonR);
	sprites->Add(10074, 180, 132, 240, 198, texSimonR);
	sprites->Add(10075, 240, 132, 300, 198, texSimonR);
	sprites->Add(10076, 300, 132, 360, 198, texSimonR);

	sprites->Add(10081, 420, 66, 480, 132, texSimonR);

	sprites->Add(10099, 180, 198, 240, 264, texSimonR);		// die 

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

	sprites->Add(11051, 180, 198, 240, 264, texSimonL);
	sprites->Add(11052, 120, 198, 180, 264, texSimonL);
	sprites->Add(11053, 60, 198, 120, 264, texSimonL);
	sprites->Add(11054, 0, 198, 60, 264, texSimonL); // nhấp nháy left
	
	sprites->Add(11061, 120, 66, 180, 132, texSimonL); // add bộ ảnh lên xuống cầu thang
	sprites->Add(11062, 180, 66, 240, 132, texSimonL);
	sprites->Add(11063, 240, 66, 300, 132, texSimonL);
	sprites->Add(11064, 300, 66, 360, 132, texSimonL);

	sprites->Add(11071, 120, 132, 180, 198, texSimonL); // add bộ ảnh đánh trái trên cầu thang
	sprites->Add(11072, 180, 132, 240, 198, texSimonL);
	sprites->Add(11073, 240, 132, 300, 198, texSimonL);
	sprites->Add(11074, 300, 132, 360, 198, texSimonL);
	sprites->Add(11075, 360, 132, 420, 198, texSimonL);
	sprites->Add(11076, 420, 132, 480, 198, texSimonL);

	sprites->Add(11081, 0, 66, 60, 132, texSimonL);

	sprites->Add(11091, 60, 66, 120, 132, texSimonL); // back
	sprites->Add(11099, 240, 198, 300, 264, texSimonL); // die

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

	ani = new Animation(100);
	ani->Add(10024);

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


	ani = new Animation(75);
	ani->Add(10051);
	ani->Add(10052);
	ani->Add(10053);
	ani->Add(10054);
	animations->Add(112, ani);

	ani = new Animation(75);
	ani->Add(11051);
	ani->Add(11052);
	ani->Add(11053);
	ani->Add(11054);
	animations->Add(113, ani);

	ani = new Animation(100); // back
	ani->Add(11091);
	animations->Add(114, ani);

	ani = new Animation(100); // lên phải
	ani->Add(10061);
	ani->Add(10062);
	animations->Add(115, ani);

	ani = new Animation(100); // xuống phải
	ani->Add(10063);
	ani->Add(10064);
	animations->Add(116, ani);

	ani = new Animation(100); // lên trái
	ani->Add(11064);
	ani->Add(11063);
	animations->Add(117, ani);

	ani = new Animation(100); // xuống trái
	ani->Add(11062);
	ani->Add(11061);
	animations->Add(118, ani);

	ani = new Animation(100); // đứng yên lên phải
	ani->Add(10062);
	animations->Add(119, ani);

	ani = new Animation(100);  // đứng yên xuống phải
	ani->Add(10064);
	animations->Add(120, ani);

	ani = new Animation(100); // đứng yên lên trái
	ani->Add(11063);
	animations->Add(121, ani);

	ani = new Animation(100); // đứng yên xuống trái
	ani->Add(11061);
	animations->Add(122, ani);

	ani = new Animation(100);  // lên đánh
	ani->Add(10073);
	ani->Add(10072);
	ani->Add(10071);
	animations->Add(123, ani);

	ani = new Animation(100); // xuống đánh
	ani->Add(10076);
	ani->Add(10075);
	ani->Add(10074);
	animations->Add(124, ani);

	

	ani = new Animation(100); // lên đánh trái
	ani->Add(11074);
	ani->Add(11075);
	ani->Add(11076);
	animations->Add(125, ani);


	ani = new Animation(100); //  xuống đánh trái
	ani->Add(11071);
	ani->Add(11072);
	ani->Add(11073);
	animations->Add(126, ani);

	ani = new Animation(100); // va chạm quái phải  
	ani->Add(10081);
	animations->Add(127, ani);

	ani = new Animation(100); //  va chạm quái trái
	ani->Add(11081);
	animations->Add(128, ani);

	ani = new Animation(100);
	ani->Add(10099);
	animations->Add(129, ani);

	ani = new Animation(100);
	ani->Add(11099);
	animations->Add(130, ani);

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
	AddAnimation(112);      // nhấp nháy
	AddAnimation(113);
	AddAnimation(114);      // back - intro;
	AddAnimation(115);		// lên phải
	AddAnimation(116);		// xuống phải
	AddAnimation(117);		// lên trái
	AddAnimation(118);		// xuống trái
	AddAnimation(119);		// đứng yên lên phải
	AddAnimation(120);		// đứng yên xuống phải
	AddAnimation(121);		// đứng yên lên trái
	AddAnimation(122);		// đứng yên xuống trái

	AddAnimation(123); // bộ ảnh đánh trên cầu thang
	AddAnimation(124);
	AddAnimation(125);
	AddAnimation(126);

	AddAnimation(127);  // bị va chạm với quái
	AddAnimation(128);

	AddAnimation(129);
	AddAnimation(130);
}


void Simon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	if (!(hp > 0))
	{
		if (start == false)
		{
			start = true;
			startTime += GetTickCount();
			SetState(SIMON_STATE_DIE);

		}

		else if (GetTickCount() - startTime > 400) // tạm chờ 1 xíu để hồi sinh
		{
			start = false;
			startTime = 0;
			Respawn(checkPoint);
			isDie = false;
			life--;
		}
	}

	

	if ( HaveWeapon && isRenderWeapon && heart > 0)
	{
		if (currentItem == ITEM_ANI_KNIFE)
		{
			knife->Update(dt, coObjects);

			if (knife->x >= x + 320 || knife->x <= x - 320)
			{
				isUseItem = false;
				isRenderWeapon = false;
			}
			if (knife->coEnemy == true)
			{
				isUseItem = false;
				isRenderWeapon = false;
			}
		}
		else if (currentItem == ITEM_ANI_AXE)
		{
			axe->Update(dt, coObjects);
			if (axe->y >= y + 300)
			{
				isUseItem = false;
				isRenderWeapon = false;
			}
			if (axe->coEnemy == true)
			{
				isUseItem = false;
				isRenderWeapon = false;
			}
		}
		else if (currentItem == ITEM_ANI_CROSS)
		{		
			cross->Update(dt, coObjects);
			if (cross->nx > 0)
			{
				if (cross->x <= x - 320)
				{
					isUseItem = false;
					isRenderWeapon = false;
				}
			}
			else
			{
				if (cross->x >= x + 320)
				{
					isUseItem = false;
					isRenderWeapon = false;
				}
			}
			if (cross->coEnemy == true)
			{
				isUseItem = false;
				isRenderWeapon = false;
			} // && cross->x - 20 <= x && cross->x + 20 >= x)
			//&& cross->x + 20 >= x)
			if (cross->isReverse == true && SweptAABBEx(cross)->nx != 0)
			{
				isUseItem = false;
				isRenderWeapon = false;
			}
		}
		else if (currentItem == ITEM_ANI_HOLYWATER)
		{
			holywater->Update(dt, coObjects);
			if (holywater->noRender == true)
			{
				isUseItem = false;
				isRenderWeapon = false;
			}
			else if (holywater->y >= y + 300)
			{
				isUseItem = false;
				isRenderWeapon = false;
			}
		}
		else if (currentItem == ITEM_ANI_STOPWATCH)
		{

				if (start == false)
				{
					isStopWatch = true;
					start = true;
					startTime += GetTickCount();

				}
				else
				{

					if (GetTickCount() - startTime > 750)
					{
						start = false;
						startTime = 0;
						isStopWatch = false;
						isUseItem = false;
						isRenderWeapon = false;
					}
				}
		}

	}

	if (vy == 0 && isJumping == true)
	{
		isJumping = false;
		isGround = true;
	}
	OnStairHandle(dt);
	if (!isOnStair)
	{
		vy += GRAVITY*dt;
	}
	GameObject::Update(dt);
	if (isIntro == true)
	{
		x += dx;
		return;
	}
	if (isColisionDoor == true)
	{
		x += dx;
		return;
	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();


	
			

	if (isHurt)
	{
		if (start == false)
		{
			start = true;
			startTime += GetTickCount();

		}
		else
		{

			if (GetTickCount() - startTime > 250)
			{
				start = false;
				startTime = 0;
				isHurt = false;
				this->SetState(SIMON_STATE_IDLE);
				reset();
			}
		}
	}


	if (isEffect)
	{
		if (start == false)
		{
			start = true;
			startTime += GetTickCount();

		}
		else
		{
			float remain = GetTickCount() - startTime;

			if (remain > SIMON_ATTACK_TIME)
			{
				start = false;
				remain = 0;
				startTime = 0;
				this->SetState(SIMON_STATE_IDLE);
				reset();
			}
		}
	}
	
	if(isFighting)
	{
		if (start == false)
		{
			start = true;
			startTime += GetTickCount();
			if (isUseItem && HaveWeapon)
			{
				if (currentItem == ITEM_ANI_KNIFE)
				{
					knife->setPositionKnife(x, y);
				}
				else if (currentItem == ITEM_ANI_AXE)
				{
					axe->setPositionAxe(x, y);
					
				}
				else if (currentItem == ITEM_ANI_CROSS)
				{
					cross->setPositionCross(x, y);		
				}
				else if (currentItem == ITEM_ANI_HOLYWATER)
				{
					holywater->setPositionHolyWater(x, y);
					
				}
			}

		}
		else
		{
			float remain =  GetTickCount() - startTime;

			if (remain > 300 && isUseItem && HaveWeapon)
			{
				isRenderWeapon = true;
			}

			if ( remain > SIMON_ATTACK_TIME)
			{		
				start = false;
				remain = 0;
				startTime = 0;
				if(isSiting)
					this->SetState(SIMON_STATE_SIT);
				else 
					this->SetState(SIMON_STATE_IDLE);
				if (isOnStair)
				{
					if (isStairLeft)
					{
						if (nx > 0)
							action = SIMON_ANI_IDLE_UP_STAIR_RIGHT;
						else
							action = SIMON_ANI_IDLE_DOWN_STAIR_LEFT;
					}
					else
					{
						if (nx > 0)
							action = SIMON_ANI_IDLE_DOWN_STAIR_RIGHT;
						else
							action = SIMON_ANI_IDLE_UP_STAIR_LEFT;
					}
				}
				reset();
				whip->reset();
			}
		}
		
	}

	//action == SIMON_ANI_ATK_RIGHT || action == SIMON_ANI_ATK_LEFT || action== SIMON_ANI_S_ATK_RIGHT || action == SIMON_ANI_S_ATK_LEFT
	if ((isFighting && isSiting && !isUseItem) || (isFighting && !isSiting && !isUseItem) )
	{
			whip->setNx(nx);
			whip->SetWhipPosition(x, y, isSiting);
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
						e->isEnable = false;
					}
				}
				else if (dynamic_cast<mCandle *>(e))
				{
					float left, top, right, bottom;
					e->GetBoundingBox(left, top, right, bottom);
					if (whip->CheckCollision(left, top, right, bottom) == true) // va chạm giữa roi và nến
					{
						e->isEnable = false;
					}
				}
				else if (dynamic_cast<Boss *>(e))
				{
					float left, top, right, bottom;
					e->GetBoundingBox(left, top, right, bottom);
					if (SweptAABBEx(e)->nx != 0 || SweptAABBEx(e)->ny != 0 || whip->CheckCollision(left, top, right, bottom) == true)
					{
						e->SetState(BOSS_STATE_HURT);
					}
				}
				else if (dynamic_cast<Enemy *>(e))
				{
					float left, top, right, bottom;
					e->GetBoundingBox(left, top, right, bottom);
					if (SweptAABBEx(e)->nx != 0 || SweptAABBEx(e)->ny != 0 || whip->CheckCollision(left, top, right, bottom) == true)
					{
						e->SetHP(dame);
						score += 100;
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
			if (dynamic_cast<Ground0 *>(e->obj))
			{
				if (isIntro == true)
				{
					y += min_ty*dy + ny*0.4f;

					if (nx != 0) vx = 0;
					if (ny != 0) vy = 0;
				}
				e->obj->GetPosition(pos.x, pos.y);
				if (nx < 0)
					iscoOLeft = true;
				else
					iscoOLeft = false;
				if (e->nx != 0)
					x += dx;
				if (e->ny != 0)
					y += dy;
				if (e->obj->nx > 0)
				{
					if ((x > pos.x - 40 && isOnStair == true) || (x > pos.x && isOnStair == true) )
					{	
						if (e->obj->state > 0)
						{
							x = pos.x - 13;
							y = pos.y + 30;
						}
						else
						{
							x = pos.x - 13;
							y = pos.y + 30;
						}
					}
					isStairTop = true;
					isStairBot = false;
				}
				else
				{

					isStairBot = true;
					isStairTop = false;
				}
				if (e->obj->state < 0)
				{
					isStairRight = true;
					isStairLeft = false;
				}
				else
				{
					isStairLeft = true;
					isStairRight = false;
				}

				if (e->nx != 0 || e->ny != 0)
				{
					if(e->obj->nx > 0)
						isOnStair = false;
				}
			}

			else if (dynamic_cast<lCandle *>(e->obj))
			{
				if (e->nx != 0)
					x += dx;
				if (e->ny != 0)
					y += dy;
			}
			else if (dynamic_cast<mCandle *>(e->obj))
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
					vy = 0;
				e->obj->isEnable = false;

				if (e->obj->GetState() == ITEM_ANI_WHIP)  
				{
					vx = 0;
					vy = 0;
					isEffect = true;
					if (whip->getType() == WHIP_NORMAL) whip->setType(WHIP_LV1);
					else if (whip->getType() == WHIP_LV1)
					{
						whip->setType(WHIP_LV2);
						isWhipMax = true;
					}
				}
				else if (e->obj->GetState() == ITEM_ANI_KNIFE)
				{
					knife = new Knife();
					HaveWeapon = true;
					currentItem = ITEM_ANI_KNIFE;
				}
				else if (e->obj->GetState() == ITEM_ANI_AXE)
				{
					axe = new Axe();
					axe->LoadResources();
					HaveWeapon = true;
					currentItem = ITEM_ANI_AXE;
				}
				else if (e->obj->GetState() == ITEM_ANI_CROSS)
				{
					cross = new Cross();
					cross->LoadResources();
					HaveWeapon = true;
					currentItem = ITEM_ANI_CROSS;
				}
				else if (e->obj->GetState() == ITEM_ANI_HOLYWATER)
				{
					holywater = new HolyWater();
					holywater->LoadResources();
					HaveWeapon = true;
					currentItem = ITEM_ANI_HOLYWATER;
				}
				else if (e->obj->GetState() == ITEM_ANI_STOPWATCH)
				{
					HaveWeapon = true;
					currentItem = ITEM_ANI_STOPWATCH;
				}
				else if (e->obj->GetState() == ITEM_ANI_BIG_HERT)
				{
					heart += 5;
					e->obj->isEnable = false;
				}
				else if (e->obj->GetState() == ITEM_ANI_SMALL_HERT)
				{
					heart += 1;
					e->obj->isEnable = false;
				}
				else if (e->obj->GetState() == ITEM_ANI_INVI)
				{
					StartUntouchable();
				}
				else if (e->obj->GetState() == ITEM_ANI_ROAST)
				{
					hp += 6;
				}
				else if (e->obj->GetState() == ITEM_ANI_DOUBLE)
				{
					dame = 2 * 2;
					updateDame = ITEM_ANI_DOUBLE;
				}
				else if (e->obj->GetState() == ITEM_ANI_TRIPLE)
				{
					dame = 2 * 3;
					updateDame = ITEM_ANI_TRIPLE;
				}
				else if (e->obj->GetState() == ITEM_ANI_ROSASY)
				{

				}
			}
			else if (dynamic_cast<Stair *>(e->obj))
			{
				if (isUpStair == false)
				{
					x += dx;
					y += min_ty*dy + ny*0.4f;
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
			else if (dynamic_cast<Door *>(e->obj))
			{
				if (!isColisionDoor)
				{
					isColisionDoor = true;
				}

			}
			else if (dynamic_cast<Bat *>(e->obj))
			{
				if (untouchable == 0)
				{
					if (!isOnStair)
					{
						if (nx > 0)
							setNx(-1);
						else setNx(1);

						SetState(SIMON_STATE_HURT);
					}
					hp -= 2;
					e->obj->isEnable = false;
					StartUntouchable();
				
				}
			}
			else if (dynamic_cast<Enemy *>(e->obj))
			{
				if (untouchable == 0)
				{
					if (!isOnStair)
					{
						if (nx > 0)
							setNx(-1);
						else setNx(1);

						SetState(SIMON_STATE_HURT);
					}
					hp -= 2;
					StartUntouchable();
					
				}
			}
			else if (dynamic_cast<Bullets *>(e->obj))
			{
				if (untouchable == 0)
				{
					if (!isOnStair)
					{
						if (nx > 0)
							setNx(-1);
						else setNx(1);

						SetState(SIMON_STATE_HURT);
					}
					hp -= 4;
					StartUntouchable();
					
				}
			}
			else if (dynamic_cast<Ground *>(e->obj))
			{
				if ((x > pos.x + 30 && iscoOLeft) ||( x < pos.x - 30 && !iscoOLeft)  )
				{
					isOnStair = false;
					isStairRight = false;
					isStairLeft = false;
					isStairBot = false;
					isStairTop = false;
				}
				 if (isOnStair && ny < 0)
				{
					isOnStair = false;
					isStairRight = false;
					isStairLeft = false;
					isStairBot = false;
					isStairTop = false;
				}
				else 
				{
					x += min_tx*dx + nx*0.4f;
					if (isHurt && !isGround)
					{
						x += dx;
						y += dy;
					}
					else
					{
						if (nx != 0)
						{
							if (!isUpStair)
								vx = 0;
							else
								x += dx;
						}

						if (ny > 0)
							y += dy;
						else
						{
							y += min_ty*dy + ny*0.4f;
							vy = 0;
						}
					}

				}
			}
		}

	}


	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Simon::Render()
{
	if (state == SIMON_STATE_DIE)
		if (nx > 0)
			action = SIMON_ANI_DIE_RIGHT;
		else
			action = SIMON_ANI_DIE_LEFT;
	else if (isOnStair)
	{
		if (isFighting)
		{
			if (isStairLeft)
			{
				if (nx > 0)
				{
					action = SIMON_ANI_ATK_UP_STAIR_RIGHT;
					stateAtk = SIMON_ANI_ATK_UP_STAIR_RIGHT;
				}
				else
				{
					action = SIMON_ANI_ATK_DOWN_STAIR_LEFT;
					stateAtk = SIMON_ANI_ATK_DOWN_STAIR_LEFT;
				}
			}
			else
			{
				if (nx > 0)
				{
					action = SIMON_ANI_ATK_DOWN_STAIR_RIGHT;
					stateAtk = SIMON_ANI_ATK_DOWN_STAIR_RIGHT;
				}
				else
				{
					action = SIMON_ANI_ATK_UP_STAIR_LEFT;
					stateAtk = SIMON_ANI_ATK_UP_STAIR_LEFT;
				}
			}
			if (isUseItem == false)
				whip->Render();
		}
	}
	else
	{
		if (!isGround && isHurt)
		{
			if(nx >0)
				action = SIMON_ANI_HURT_RIGHT;
			else
				action = SIMON_ANI_HURT_LEFT;
		}
		if (isEffect)
		{
			if (nx > 0)
				action = SIMON_ANI_EFFECT_RIGHT;
			else
				action = SIMON_ANI_EFFECT_LEFT;
		}
		else if (isBack == true)
		{
			action = SIMON_ANI_BACK;
		}
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
				if (nx > 0)
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
			if ((heart <= 0 && isUseItem))
			{
				if (nx > 0)
					action = SIMON_ANI_IDLE_RIGHT;
				else
					action = SIMON_ANI_IDLE_LEFT;
			}
			else
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
				if (isUseItem == false)
					whip->Render();
			}
		}
		else if (isFighting && isSiting && !isStairLeft && !isStairRight)
		{
			if ((heart <= 0 && isUseItem))
			{
				if (nx > 0)
					action = SIMON_ANI_SIT_RIGHT;
				else
					action = SIMON_ANI_SIT_LEFT;
			}
			else
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
				if (isUseItem == false)
					whip->Render();
			}
		}
	}
	if (isRenderWeapon && heart > 0)
	{
		if (currentItem == ITEM_ANI_KNIFE)
			knife->Render();
		else if (currentItem == ITEM_ANI_AXE)
			axe->Render();
		else if (currentItem == ITEM_ANI_CROSS)
			cross->Render();
		else if (currentItem == ITEM_ANI_HOLYWATER)
			holywater->Render();
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
		vy = -SIMON_JUMP_SPEED_Y;

		break;
	case SIMON_STATE_IDLE:
		isFighting = false;
		isJumping = false;
		isSiting = false;
		isGround = true;
		vx = 0;
		isEffect = false;
		break;
	case SIMON_STATE_DIE:
		vy = -SIMON_DIE_DEFLECT_SPEED;
		isDie = true;
		break;
	case SIMON_STATE_SIT:
		isFighting = false;
		isJumping = false;
		isSiting = true;
		isGround = true;

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
		isGround = true;
		isUseItem = true;
		vx = 0;
		heart--;
		if (currentItem == ITEM_ANI_KNIFE)
		{
			if (isSiting == true)
				knife->isSit = true;
			else knife->isSit = false;
			knife->setPositionKnife(x, y);
			knife->coEnemy = false;
			knife->setNx(nx);
		}
		else if (currentItem == ITEM_ANI_AXE)
		{
			if (isSiting == true)
				axe->isSit = true;
			else axe->isSit = false;
			axe->setPositionAxe(x, y);
			axe->coEnemy = false;
			axe->setNx(nx);
		}
		else if (currentItem == ITEM_ANI_CROSS)
		{
			if (isSiting == true)
				cross->isSit = true;
			else cross->isSit = false;
			cross->setPositionCross(x, y);
			cross->coEnemy = false;
			cross->isReverse = false;
			cross->setNx(nx);
		}
		else if (currentItem == ITEM_ANI_HOLYWATER)
		{
			if (isSiting == true)
				holywater->isSit = true;
			else holywater->isSit = false;
			holywater->setPositionHolyWater(x, y);
			holywater->setNx(nx);
		}
		
		
		
		
		break;
	case SIMON_STATE_CHANGE:
		//isOnStair = true;

		isUpStair = false;
		isOnStair = true;
		directionX = 1;
		directionY = -1;
		vx = 0;
		break;
	case SIMON_STATE_HURT:
		isGround = false;
		isHurt = true;
		vy -= SIMON_WALKING_SPEED * 3;
		if (nx > 0)
			vx -= SIMON_WALKING_SPEED * 2;
		else
			vx = SIMON_WALKING_SPEED * 2;
		break;
	}
	

}


void Simon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x + 15;
	top = y;
	right = x + SIMON_BBOX_WIDTH +2;
	bottom = y + SIMON_BBOX_HEIGHT;

}

void Simon::Respawn(D3DXVECTOR2 point)
{
	SetState(SIMON_STATE_IDLE);
	SetPosition(point.x, point.y);
	HaveWeapon = false;
	isUseItem = false;
	isOnStair = false;
	isStairRight = false;
	isStairLeft = false;
	isStairBot = false;
	isStairTop = false;
	hp = 16;
	isDie = false;
}

void Simon::OnStairHandle(DWORD dt)
{
	if (isStairBot && isStairLeft && !isOnStair)
	{
		if (IsKeyDown(DIK_UP))
		{
			if ((x + 24 > pos.x) && (x < pos.x + 24) && !isOnStair)
			{
				isUpStair = true;
				isOnStair = false;
				nx = -1;
				SetState(SIMON_STATE_WALK);
			}
			else
			{
				isUpStair = false;
				isOnStair = true;
				directionX = 1;
				directionY = 1;
			}
		}

	}
	else if (isStairBot && isStairRight && !isOnStair)
	{
		if (IsKeyDown(DIK_UP))
		{
			if ((x + 48 > pos.x) && (x < pos.x ) && !isOnStair)
			{
				isUpStair = true;
				isOnStair = false;
				nx = 1;
				SetState(SIMON_STATE_WALK);
			}
			else 
			{
				isUpStair = false;
				isOnStair = true;
				directionX = -1;
				directionY = 1;
			}
			
		}
	}
	if (isStairTop && isStairLeft && !isOnStair)
	{
		if (IsKeyDown(DIK_DOWN))
		{
			if ((x + 30 > pos.x) && (x < pos.x + 24) && !isOnStair)
			{
				isUpStair = true;
				isOnStair = false;
				nx = -1;
				SetState(SIMON_STATE_WALK);
			}
			else
			{
				isUpStair = false;
				isOnStair = true;
				directionX = -1;
				directionY = -1;
			}
		}
	}
	else if (isStairTop && isStairRight && !isOnStair)
	{
		if (IsKeyDown(DIK_DOWN))
		{
			if ((x + 56 > pos.x) && (x < pos.x + 10) && !isOnStair)
			{
				isUpStair = true;
				isOnStair = false;
				nx = 1;
				SetState(SIMON_STATE_WALK);
			}
			else
			{
				isUpStair = false;
				isOnStair = true;
				directionX = 1;
				directionY = -1;
			}
		}
	}
	if (isOnStair)
	{
		if (directionX * directionY > 0)
		{
			if (IsKeyDown(DIK_DOWN))
			{
				action = SIMON_ANI_DOWN_STAIR_LEFT;
				nx = -1;
				vx = -SIMON_WALKING_SPEED + 0.02f;
				vy = SIMON_WALKING_SPEED - 0.02f;
			}
			else if (IsKeyDown(DIK_UP))
			{
				action = SIMON_ANI_UP_STAIR_RIGHT;
				nx = 1;
				vx = SIMON_WALKING_SPEED - 0.02f;
				vy = -SIMON_WALKING_SPEED  + 0.02f;
			}
		}
		else if (directionX * directionY < 0)
		{
			if (IsKeyDown(DIK_DOWN))
			{
				action = SIMON_ANI_DOWN_STAIR_RIGHT;
				nx = 1;
				vx = SIMON_WALKING_SPEED - 0.02f;
				vy = SIMON_WALKING_SPEED - 0.02f;
			}
			else if (IsKeyDown(DIK_UP))
			{
				action = SIMON_ANI_UP_STAIR_LEFT;
				nx = -1;
				vx = -SIMON_WALKING_SPEED + 0.02f;
				vy = -SIMON_WALKING_SPEED + 0.02f;
			}
		}
	}
	if ((IsKeyRelease(DIK_DOWN) || IsKeyRelease(DIK_UP)) && isOnStair)
	{
		if (vy < 0)
		{
			if (nx > 0)
				action = SIMON_ANI_IDLE_UP_STAIR_RIGHT;
			else
				action = SIMON_ANI_IDLE_UP_STAIR_LEFT;
		}
		else
		{
			if (nx > 0)
				action = SIMON_ANI_IDLE_DOWN_STAIR_RIGHT;
			else
				action = SIMON_ANI_IDLE_DOWN_STAIR_LEFT;
		}
		isFighting = false;
		vx = 0;
		vy = 0;
	}
}

void Simon::reset()
{
	animations[stateAtk]->setCurrentFrame(-1);
}
