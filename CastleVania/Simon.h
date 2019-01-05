#pragma once
#include "GameObject.h"
#include "Whip.h"
#include "Items.h"
#include "Knife.h"
#include "Zombie.h"
#include "Stair.h"
#include "Ground_Null.h"
#include "Door.h"
#include "Panther.h"
#include "mCandle.h"
#include "EffectDead.h"
#include "Boss.h"
#include "Grid.h"
#include "Bullets.h"
#include "Axe.h"
#include "Cross.h"
#include "HolyWater.h"
#include "Bat.h"
#include "Cross.h"
class Simon : public GameObject
{
	int hp;
	int life;
	int heart;
	int score;
	int dame;
	bool isHurt;
	bool iscoOLeft;
	D3DXVECTOR2 pos;
	int startTime;
	bool start;
	Whip *whip;
	Knife *knife;
	Axe * axe;
	Cross * cross;
	HolyWater *holywater;
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
	bool isBack;
	bool isEffect;
	bool isStairLeft;
	bool isStairRight;
	bool isStairBot;
	bool isStairTop;
	bool isOnStair;
	bool isUpStair;
	int directionX;
	int directionY;
	bool isColisionDoor;
	bool isDie;
	D3DXVECTOR2 checkPoint;
	bool isWhipMax;
	bool isRenderWeapon;
	bool isStopWatch;
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
	bool checkEffect() { return isEffect; }
	bool checkStair() { return isOnStair; }
	bool checkColisionDoor() { return isColisionDoor; }
	bool checkHurt() { return isHurt; }
	bool checkWhip() { return isWhipMax; }
	bool checkDie() { return isDie; }
	bool checkUseItem() { return isUseItem; }
	bool checkStopWatch() { return isStopWatch; }
	void setStair(bool status) { this->isOnStair = status; }
	void setColisionDoor(bool coO) { this->isColisionDoor = coO; }
	void OnStairHandle(DWORD dt);
	void setBack(bool check) { isBack = check; }
	void reset();
	void setCheckPoint(D3DXVECTOR2 point) { this->checkPoint = point; }
	D3DXVECTOR2 getCheckPoint() { return checkPoint; }
	int getHeart() { return heart; }
	int getLife() { return life; }
	int getScore() { return score; }
	void setLife(int dame) { life -= dame; }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Respawn(D3DXVECTOR2 point);
	virtual int GetHP() { return this->hp; }
	virtual void SetHP(int dame) { this->hp = hp - dame; }
	bool isIntro;
	int currentItem;
	int updateDame;
	Simon();
};