#pragma once

#include "GameObject.h"
class Candle : public GameObject
{
private:
	Animation *anim;
	void InitAnim();
public:
	bool Initialize(LPDIRECT3DDEVICE9 gDevice, const char* file, float x, float y, int tag);
	void Render(Camera *cam);
	void Update(float gameTime);
	Candle();
	~Candle();
};