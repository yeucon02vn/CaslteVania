#pragma once
#include "GameObject.h"
#include "Textures.h"


class Stair : public GameObject
{
	int count;
public:
	virtual void LoadResources();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	void setCount(int sL) { this->count = sL; }
};