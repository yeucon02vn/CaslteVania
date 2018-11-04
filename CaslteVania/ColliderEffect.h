#pragma once
#include "Sprite.h"

class ColliderEffect
{
private:
	Sprite *sprite;
	bool isVisible;
	float timeDelay;
public:
	ColliderEffect();
	~ColliderEffect();

	bool Initialize(LPDIRECT3DDEVICE9 gDevice, const char* file, float x, float y);
	void Render(Camera *cam);
	void Update(float gameTime);
	void SetPosition(float x, float y);
	void SetVisible(bool _isVisible) { isVisible = _isVisible; }
};
