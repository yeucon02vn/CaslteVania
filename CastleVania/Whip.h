#pragma once

#include "GameObject.h"
#include "Textures.h"
#include "Global.h"
#include "lCandle.h"

class Whip : public GameObject
{
	
	int type;
	int action;
public:
	Whip() : GameObject() {}

	void Update();
	void Render();
	void reset();
	void setType(int _type) { this->type = _type; }
	int getType() { return this->type; }
	void SetWhipPosition(float x, float y, bool isSit);
	bool CheckCollision(float obj_left, float obj_top, float obj_right, float obj_bottom);
	virtual void LoadResources();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};
