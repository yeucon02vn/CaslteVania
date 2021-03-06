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
using namespace std;
class TileMap
{
private:

	Sprites *sprites;
	Textures * textures;
	Animation *AniTile;
	int RowMatrix = 0; // dòng và cột của ma trận
	int ColumnMatrix = 0;
	int Tile_Map[500][176];
	int fit;

	int column, row;
	int ScreenRow;
	int ScreenColumn;
	int x, y;
	int FrameWidth;
	int FrameHeight;
public:
	
	TileMap(int state);
	~TileMap();
	bool isCheck;
	void ReadMap(LPCWSTR filename, int State);
	void LoadMap(int state);
	void DrawMap(D3DXVECTOR2 cam);
	void Draw();
	//void DrawMap(Camera * cam);

};
