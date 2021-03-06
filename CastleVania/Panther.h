#pragma once
#include "Enemy.h"
#include "Textures.h"
#include "Ground.h"
#include "Ground_Null.h"
class Panther : public Enemy
{
	bool isJump;
	bool isGround;
	bool isCheck;
public:
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void LoadResources();
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void SetState(int state);
	virtual void Run(float sx)
	{
		if (sx < x + 150 && sx > x - 150)
		{
			isRun = true;
		}
	}
	virtual void Reload(float sx)
	{
		if (sx > x + 500 || sx < x - 500)
		{
			if (sx < x)
				nx = -1;
			else
				nx = 1;
			x = preX;
			y = preY;
			isEnable = true;
			isRun = false;
			isGround = false;
			isCheck = false;
			isJump = false;
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