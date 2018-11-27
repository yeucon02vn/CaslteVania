#pragma once
#include "GameObject.h"
#include "Textures.h"


class lCandle : public GameObject
{
public:
	virtual void LoadResources();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
};