#pragma once
#include "GameObject.h"
#include "Textures.h"
#include "Global.h"
#include "Ground.h"
class Items : public GameObject
{
private:
	DWORD timeDelete;   // dùng để hủy item sau 1 khoảng time
	bool isLv2;
public:
	Items();
	
	virtual void LoadResources();
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	int Random();
	void RandomItem();
	void RandomSubWeapon();
	void setLv2() { isLv2 = true; }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

typedef Items * LPITEMS;