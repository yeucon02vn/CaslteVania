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
	x += dx;
}

void Knife::setPositionKnife(float x, float y)
{
	if (nx > 0)
		x += 50;

	y += 15;
	SetPosition(x, y);
}


void Knife::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + KNIFE_BBOX_WIDTH;
	bottom = top + KNIFE_BBOX_HEIGHT;
}

