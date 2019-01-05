#pragma once
#include "Enemy.h"
#include "Textures.h"
#include "Global.h"

class Bat : public Enemy
{
	int defaultY;
public:
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void LoadResources();
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void SetState(int state);
	virtual void Run(float sx)
	{
		if (sx > x - 450 && sx < x + 450)
		{
			if (sx > x)
				nx = 1;
			else
				nx = -1;
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
			hp = 1;
		}
	}
	void setPre(float x, float y)
	{
		preX = x;
		preY = y;
	}
};