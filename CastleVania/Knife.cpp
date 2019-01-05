#include "Knife.h"



Knife::Knife() : GameObject()
{
	vx = ITEM_Knife_SPEED;
	AddAnimation(502);
	AddAnimation(503);
}

void Knife::LoadResources()
{
}

void Knife::Render()
{
	if (nx > 0)
		animations[0]->Render(x, y);
	else
		animations[1]->Render(x, y);
}

void Knife::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (nx < 0) vx = -ITEM_Knife_SPEED;
	else vx = ITEM_Knife_SPEED;

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
void Knife::setPositionKnife(float x, float y)
{
	if (nx > 0)
		x += 50;

	y += 15;
	if (isSit == true)
		y += 15.0f;
	SetPosition(x, y);
}


void Knife::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + KNIFE_BBOX_WIDTH;
	bottom = top + KNIFE_BBOX_HEIGHT;
}

