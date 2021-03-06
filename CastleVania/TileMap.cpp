#include "TileMap.h"
TileMap::TileMap(int state)
{
	LoadMap(state);
}

TileMap::~TileMap()
{

}

void TileMap::ReadMap(LPCWSTR filename, int State)
{
	ifstream file;
	file.open(filename, ios::in);

	switch (State)
	{
	case 1: ColumnMatrix = 48;	fit = 164; break;
	case 2: ColumnMatrix = 176; fit = 130;  break;
	default:; break;
	}

	while (!file.eof())
	{
		for (int j = 0; j < ColumnMatrix; j++)
		{
			file >> Tile_Map[RowMatrix][j];
		}
		RowMatrix++;
	}
}

void TileMap::LoadMap(int state)
{
	textures = Textures::GetInstance();
	sprites = Sprites::GetInstance();
	switch (state)
	{
	case MENU_STATE:
	{
		textures->Add(ID_TEX_MENU_SCREEN, MENU_SCREEN, D3DCOLOR_XRGB(255, 255, 255));
		LPDIRECT3DTEXTURE9 Menu = textures->Get(ID_TEX_MENU_SCREEN);
		sprites->Add(70001, 0, 0, 640, 480, Menu);
		AniTile = new Animation(0);
		AniTile->Add(70001);
		break;
	}
	case INTRO_STATE:
	{
		textures->Add(ID_TEX_INTRO_SCREEN, INTRO_SCREEN, D3DCOLOR_XRGB(255, 255, 255));
		LPDIRECT3DTEXTURE9 Intro = textures->Get(ID_TEX_INTRO_SCREEN);
		sprites->Add(80001, 0, 0, 640, 480, Intro);
		AniTile = new Animation(0);
		AniTile->Add(80001);
		break;
	}
	case STATE_LV1:
	{
		ReadMap(L"Resource\\sprites\\lv1.txt", STATE_LV1);

		textures->Add(ID_TEX_LEVEL_ONE, L"Resource\\sprites\\lv1.png", D3DCOLOR_XRGB(255, 255, 255));

		LPDIRECT3DTEXTURE9 state1 = textures->Get(ID_TEX_LEVEL_ONE);
		for (int i = 0; i < 50; i++)
			sprites->Add(300000 + i, i * 32, 0, 32 + i * 32, 32, state1);


		AniTile = new Animation(0);
		for (int i = 0; i < 50; i++)
			AniTile->Add(300000 + i);

		FrameWidth = sprites->Get(300000)->getWidth();
		FrameHeight = sprites->Get(300000)->getHeight();
		ScreenRow = (SCREEN_HEIGHT / FrameHeight);
		break;
	}
	case STATE_LV2:
		ReadMap(L"Resource\\sprites\\lv2.txt", STATE_LV2);

		textures->Add(ID_TEX_LEVEL_TWO, L"Resource\\sprites\\lv2.png", D3DCOLOR_XRGB(255, 255, 255));
		LPDIRECT3DTEXTURE9 state2 = textures->Get(ID_TEX_LEVEL_TWO);
		for (int i = 0; i < 114; i++)
			sprites->Add(310000 + i, i * 32, 0, 32 + i * 32, 32, state2);


		AniTile = new Animation(0);
		for (int i = 0; i < 114; i++)
			AniTile->Add(310000 + i);

		FrameWidth = sprites->Get(310000)->getWidth();
		FrameHeight = sprites->Get(310000)->getHeight();
		ScreenRow = (SCREEN_HEIGHT / FrameHeight); 
		break;
	}



}



//Vẽ lại hàm drawmap(Updated)
void TileMap::DrawMap(D3DXVECTOR2 cam)
{
	
	int colStart = cam.x / FrameWidth;
	int colEnd = ((cam.x + SCREEN_WIDTH) / FrameWidth + 2);

	for (int i = 0; i < ScreenRow; i++)
	{
		for (int j = colStart; j < colEnd; j++)
		{
			x = FrameWidth * (j - colStart) + cam.x - (int)cam.x % 32;
			y = i * FrameHeight + fit;
			if (isCheck == false)
			{
				AniTile->setCurrentFrame(Tile_Map[i][j]);
				AniTile->Draw(x, y);
			}
			else
			{
				AniTile->setCurrentFrame(Tile_Map[i + 11][j]);
				AniTile->Draw(x, y+ 480);
			}
		}
	}
}

void TileMap::Draw()
{
	AniTile->setCurrentFrame(0);
	AniTile->Draw(0, 0);
}

