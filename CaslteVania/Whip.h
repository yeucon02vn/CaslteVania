#pragma once

#include "Animation.h"
#include "DeadAnimation.h"
#include "GameObject.h"

#define NORMAL_WHIP		0
#define VAMPIRE_KILLER	1
#define CHAIN_WHIP		2
#define MORNING_STAR	3

class Whip : public GameObject
{
private:
	Animation *anim;
	int type;
	bool isLeft;
	bool check; //kiem tra xem roi da xet va cham chua
public:
	Whip();
	~Whip();

	bool Initialize(LPDIRECT3DDEVICE9 gDevice, const char* file, float x, float y, int tag);
	void Render(Camera *cam);
	void Update(float gameTime);

	void SetPosition(D3DXVECTOR3 _position, bool isStanding);

	void SetIsLeft(bool _isLeft);

	void SetType(int _type);

	D3DXVECTOR3 GetVelocity() { return D3DXVECTOR3(0, 0, 0); }

	void CheckCollider(float gameTime, std::vector<GameObject*> *listGameObject);
	void CheckColliderWith(float gameTime, GameObject *object);

	int GetCurrentFrameOfWhip() { return anim->GetCurrentFrame(); }


};

