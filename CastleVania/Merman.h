#pragma once
#include "Enemy.h"
#include "Textures.h"
#include "Global.h"
#include "Ground.h"
#include "Bullets.h"
#include "EffectDead.h"
#include "Grid.h"

class Merman : public Enemy
{
	int ani;
	bool isFire;
	Bullets *bullet;
	bool isJump;
	bool isGround;
	bool isFalling;
	bool isIdle;
	bool isCreateEffect;
	EffectDead * effect;
	Grid * grid;
public:
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void LoadResources();
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void SetState(int state);
	virtual void Run(float sx)
	{
		if (isMapWater)
		{
			if (sx > x)
				nx = 1;
			else
				nx = -1;
			if (sx > x - 100 && sx < x + 100)
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
			isGround = false;
			isFalling = false;
			isJump = false;
			isIdle = false;
			isCreateEffect = false;
			isFire = false;
			isMapWater = false;
			hp = 1;
		}
	}
	void setPre(float x, float y)
	{
		preX = x;
		preY = y;
	}

	bool isMapWater;
};