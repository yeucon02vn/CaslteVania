#pragma once
#include "GameObject.h"
#include "Whip.h"
#include "Items.h"
#include "Knife.h"
class Simon : public GameObject
{
	int fightTime;
	bool startFight;
	Whip *whip;
	Knife *knife;
	bool isJumping;
	bool isSiting;
	bool isFighting;
	bool isFalling;
	bool isGround;
	int untouchable;
	int action;
	DWORD untouchable_start;
	bool HaveWeapon;
	int stateAtk;
	bool isUseItem;
	
public:
	int getTypeofWhip() { return whip->getType(); }
	bool KillAllKey;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	virtual void LoadResources();
	bool checkFight() { return isFighting; }
	bool checkJump() { return isJumping; }
	bool checkFall() { return isFalling; }
	bool checkSit() { return isSiting; }
	bool checkGround() { return isGround; }
	bool checkWeapon() { return HaveWeapon; }
	void reset();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	Simon();
};