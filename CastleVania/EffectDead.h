#pragma once
#include "GameObject.h"
#include "Textures.h"


class EffectDead : public GameObject
{
	int count;
public:
	//bool isSplashing;
	virtual void LoadResources();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
};