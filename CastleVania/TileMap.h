#pragma once
#include <stdio.h>
#include <conio.h>
#include "Sprites.h"
#include "Animations.h"
#include "Textures.h"
#include "Global.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Camera.h"
using namespace std;
class TileMap
{
private:
	Sprites *sprites;
	int RowMatrix = 0; // dòng và cột của ma trận
	int ColumnMatrix = 0;
	int Tile_Map[500][176];
	int fit = 160;

	int column, row;
	int ScreenRow;
	int ScreenColumn;
	int x, y;
	int FrameWidth;
	int FrameHeight;
public:
	Textures * textures;
	Animation *AniTile;
	Animations *ani;
	TileMap();
	~TileMap();
	void ReadMap(LPCWSTR filename);
	void LoadMap();
	void DrawMap(D3DXVECTOR2 cam);
	//void DrawMap(Camera * cam);

};
