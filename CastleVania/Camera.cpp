#include "Camera.h"

Camera::Camera(float x)
{
	this->viewport.x = x - 15;
	this->viewport.y = SCREEN_HEIGHT;
}


Camera::~Camera()
{
}

D3DXVECTOR2 Camera::SetPositionInCamera(D3DXVECTOR3 position)
{
	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt); 


	mt._22 = -1.0f;
	mt._41 = -this->viewport.x;
	mt._42 = this->viewport.y;

	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos, &position, &mt);

	return D3DXVECTOR2(vp_pos.x, vp_pos.y);
}

void Camera::SetCameraPosition(float x, float y)
{
	this->viewport.x = x;
	this->viewport.y = y;
}

D3DXVECTOR2 Camera::GetCameraPosition()
{
	return this->viewport;
}
