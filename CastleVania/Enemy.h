#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
protected:
	int hp;
	int hpC;
	int damage;
	int point;
	bool isRun;
	float preX;
	float preY;
	
public:
	Enemy();
	Enemy(int hp, int damage, int point);
	~Enemy();
	virtual int GetHP() { return this->hp; }
	virtual void SetHP(int dame) { this->hp = hp - dame; }
	virtual void Run(float sx) = 0;
	virtual void Reload(float sx) { }
	bool reload;
	bool checkRun() { return isRun; }
};