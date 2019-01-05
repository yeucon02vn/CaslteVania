#pragma once
#include "Enemy.h"
#include "Textures.h"
#include "Global.h"
#include "Ground.h"

class Zombie : public Enemy
{
public:
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void LoadResources();
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void SetState(int state);

	virtual void Run(float sx)
	{
		if (sx < x + 320 && sx > x - 320)
		{
			isRun = true;
		}
	}
	virtual void Reload(float sx)
	{
		if (sx > x + 600 || sx < x - 600)
		{
			if (sx < x)
				nx = -1;
			else
				nx = 1;
			x = preX;
			y = preY;
			isEnable = true;
			isRun = false;
			reload = true;
			hp = 1;
		}
	}
	void setPre(float x, float y)
	{
		preX = x;
		preY = y;
	}
	float getPrex() { return preX; }
};