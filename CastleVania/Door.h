#pragma once
#include "GameObject.h"
#include "Textures.h"


class Door : public GameObject
{
public:
	bool isOpenDoor;
	bool isHoldDoor;
	virtual void LoadResources();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
};