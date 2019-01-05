#pragma once

#include "GameObject.h"
#include "Animations.h"
#include "Textures.h"
#include "Ground.h"
#include "Enemy.h"
#include "Boss.h"

class HolyWater : public GameObject
{
	bool isGround;
	bool start;
	int startTime;
public:
	HolyWater();
	bool isSit;
	bool noRender;
	virtual void LoadResources();
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void setPositionHolyWater(float x, float y);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

