#include "Enemy.h"

Enemy::Enemy()
{
	isRun = false;
	hp =1;
	point = 100;
	damage = 2;
}

Enemy::Enemy(int hp, int damage, int point)
{
	isRun = false;
	this->hp = hp;
	this->damage = damage;
	this->point = point;
}

Enemy::~Enemy()
{
}