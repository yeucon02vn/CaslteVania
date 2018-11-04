#include "ColliderEffect.h"



ColliderEffect::ColliderEffect()
{
}


ColliderEffect::~ColliderEffect()
{
}

bool ColliderEffect::Initialize(LPDIRECT3DDEVICE9 gDevice, const char* file, float x, float y)
{
	if (!sprite)
	{
		sprite = new Sprite(x, y);
		if (!sprite->Initialize(gDevice, file))
			return false;
	}
	timeDelay = 0.0f;
	isVisible = false;
	return true;
}

void ColliderEffect::Render(Camera *cam)
{
	if (isVisible)
		sprite->Render(cam);
}

void ColliderEffect::Update(float gameTime)
{
	if (isVisible)
	{
		timeDelay += gameTime;
		if (timeDelay > 0.45f)
		{
			timeDelay = 0.0f;
			isVisible = false;
		}
	}
}

void ColliderEffect::SetPosition(float x, float y)
{
	sprite->SetPosition(x, y);
}