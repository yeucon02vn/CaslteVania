#pragma once

#include "GameObject.h"
#include "Animations.h"
#include "Textures.h"
#include "Ground.h"
#include "Enemy.h"
#include "Boss.h"

class Axe : public GameObject
{
	int preY;
	bool isFalling;

public:
	Axe();
	bool isSit;
	bool coEnemy;
	virtual void LoadResources();
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void setPositionAxe(float x, float y);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

