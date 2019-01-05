#pragma once
#include "Enemy.h"
#include "Textures.h"
#include "Global.h"

#define HURT_TIME	10
#define WAIT_TIME	1000
#define CHASE_TIME	300

#define BOSS_ANI_SLEEP 0
#define BOSS_ANI_HURTED 1
#define BOSS_ANI_FLY 2

#define BOSS_BBOX_WIDTH 100
#define BOSS_BBOX_HEIGHT 46
#define BOSS_STATE_HURT 1

class Boss : public Enemy
{
	
	D3DXVECTOR2 direction;
	D3DXVECTOR2 random;
	D3DXVECTOR2 simonPos;

	bool start;
	bool atSpot;
	bool aimable;
	float distance;
	int hurtTime;
	bool isHurt;
	float waitTime;
	float chaseTime;
	//bool isCheck;
	float preX;
	float preY;
public:
	Boss(int hp, int damage, int point);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void LoadResources();
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Run(float sx)
	{
		if (sx > x + 50 )
		{
			isRun = true;
		}
	}
	virtual void SetState(int state);
	void AimSimon(LPGAMEOBJECT simon, DWORD dt);
	void RandomSpot();
	void Fly(float gameTime);
	void FlyToRandomSpot(float gameTime);
	void setPoisitionBoss(float x, float y)
	{
		SetPosition(x, y);
		preX = x - 320;
		preY = y - 10;
	}
	void SimonDie()
	{
		isRun = false;
		state = BOSS_ANI_SLEEP;
		atSpot = true;
		aimable = false;
		waitTime = 0;
		hurtTime = HURT_TIME;
		isHurt = false;
		this->hp = 16;
		this->damage = 2;
		this->point = 1000;
		simonPos.x = -1;
	}
};