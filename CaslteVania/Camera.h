#pragma once
#include <d3dx9.h>

class Camera
{
private:
	D3DXVECTOR3 cameraPosition;     //Toa do cua camera trong world
	RECT *region;
	
public:
	Camera(float x, float y);
	~Camera();

	//Chuyen tu toa do trong the gioi thuc sang toa do trong Camera
	D3DXVECTOR3 SetPositionInCamera(D3DXVECTOR3 position);

	//Set toa do cua camera trong world(di chuyen camera)
	void SetCameraPosition(float x, float y);

	//Lay toa do cua camera trong the gioi thuc
	D3DXVECTOR3 GetCameraPosition();
};

