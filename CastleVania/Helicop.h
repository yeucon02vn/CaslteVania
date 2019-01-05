#pragma once
#include "GameObject.h"
#include "Textures.h"

class Helicop : public GameObject
{
public:
	virtual void LoadResources();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void GetBoundingBox(float & left, float & top, float & right, float & bottom);
};