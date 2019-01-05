#pragma once
#include "GameObject.h"
#include "Textures.h"


class Bullets : public GameObject
{
public:
	virtual void LoadResources();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void setPositionBullet(float x, float y);
};