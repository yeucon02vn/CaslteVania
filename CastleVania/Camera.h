#pragma once
#include "Global.h"
#include "Sprites.h"


class Camera
{
private:
	D3DXVECTOR2 viewport;     //Toa do cua camera trong world
	RECT *region;

public:
	Camera(float x);
	~Camera();

	D3DXVECTOR2 SetPositionInCamera(D3DXVECTOR3 position);

	void SetCameraPosition(float x, float y);

	D3DXVECTOR2 GetCameraPosition();
};

