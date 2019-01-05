#pragma once
#include "GameObject.h"
#include "Items.h"
#include "EffectDead.h"
class Grid
{
	vector<LPGAMEOBJECT>* objects;

	LPGAMEOBJECT simon;

	static Grid* instance;

	float gridHeight, gridWidth;

	int mapHeight, mapWidth;
	
public:
	static Grid* GetInstance();
	Grid();
	~Grid();
	bool isStopWatch;
	void GetMapSize(int x, int y);
	void AddObject(LPGAMEOBJECT a);
	void AddSimon(LPGAMEOBJECT _simon) { simon = _simon; }

	void Draw(int xcam, int ycam, int h, int w);
	void Update(int xcam, int ycam, int h, int w, DWORD dt);
	void DeleteEnable();
	void Clear();



};