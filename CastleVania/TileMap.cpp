#include "TileMap.h"
TileMap::TileMap()
{
	LoadMap();
}

TileMap::~TileMap()
{

}

void TileMap::ReadMap(LPCWSTR filename)
{
	ifstream file;
	file.open(filename, ios::in);

	ColumnMatrix = 48;

	while (!file.eof())
	{
		for (int j = 0; j < ColumnMatrix; j++)
		{
			file >> Tile_Map[RowMatrix][j];
		}
		RowMatrix++;
	}
	int a = RowMatrix;
}

void TileMap::LoadMap()
{
	
	ReadMap(L"Resource\\sprites\\lv1.txt");
	textures = Textures::GetInstance();
	textures->Add(ID_LEVEL_ONE_MATRIX_BG, L"Resource\\sprites\\lv1.jpg", D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 state1 = textures->Get(ID_LEVEL_ONE_MATRIX_BG);

	sprites = Sprites::GetInstance();
	for(int i = 0; i< 50; i++)
		sprites->Add(30000 +i,  i * 32, 0, 32 + i * 32, 32, state1);


	AniTile = new Animation(0);
	for (int i = 0; i < 50; i++)
		AniTile->Add(30000 + i);

	//ani->Add(10, AniTile);
	FrameWidth = sprites->Get(30000)->getWidth();
	FrameHeight = sprites->Get(30000)->getHeight();
	ScreenRow = (SCREEN_HEIGHT / FrameHeight);
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
			y = i * FrameHeight + 164;
			AniTile->setCurrentFrame(Tile_Map[i][j]);
			AniTile->Draw(x, y);
				
		}
	}
}

//void TileMap::DrawMap(Camera * cam)
//{
//			row = int(cam->GetCameraPosition().y) / FrameHeight; //5
//			column = int(cam->GetCameraPosition().x) /FrameHeight; // 448
//		
//			x = -(int(cam->GetCameraPosition().x) % FrameHeight); //-5
//			y = (int(cam->GetCameraPosition().y) % FrameHeight);  //0
//		
//			for (int i = 0; i < ScreenRow; i++)
//			{
//				if (y >= fit)
//				{
//					for (int j = 0; j < ScreenColumn; j++)
//					{
//						if (!(RowMatrix - row + i < 0 || RowMatrix - row + i >= RowMatrix))
//						{
//							AniTile->setCurrentFrame(Tile_Map[RowMatrix - row + i][column + j]);
//							AniTile->DrawFromTL(x, y);
//							x = x + FrameHeight;
//						}
//					}
//				}
//				y = y + FrameHeight;
//				x = -int(cam->GetCameraPosition().x) % FrameHeight;
//			}
//}


