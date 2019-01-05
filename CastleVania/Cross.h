#pragma once
#include "GameObject.h"
#include "Animations.h"
#include "Textures.h"
#include "Ground.h"
#include "Enemy.h"
#include "Boss.h"

class Cross : public GameObject
{
	int preX;
	

public:
	Cross();
	bool isSit;
	bool coEnemy;
	bool isReverse;
	virtual void LoadResources();
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void setPositionCross(float x, float y);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

