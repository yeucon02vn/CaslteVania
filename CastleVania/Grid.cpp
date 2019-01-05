#include "Grid.h"

Grid* Grid::instance = NULL;

Grid::Grid()
{
	objects = new vector<LPGAMEOBJECT>[4];
}


Grid * Grid::GetInstance()
{
	if (instance == NULL) instance = new Grid();
	return instance;
}

Grid::~Grid()
{
}

void Grid::GetMapSize(int x, int y)
{
	mapWidth = x;
	mapHeight = y;
	gridWidth = x / 4.;
}

void Grid::AddObject(LPGAMEOBJECT a)
{
	float tempx;
	a->getX(tempx);

	if (tempx < gridWidth)
		objects[0].push_back(a);
	else if (tempx < gridWidth * 2)
		objects[1].push_back(a);
	else if (tempx < gridWidth * 3)
		objects[2].push_back(a);
	else objects[3].push_back(a);
}

void Grid::Draw(int xcam, int ycam, int w, int h)
{
	//Grid 1
	if (xcam < gridWidth && xcam + w < gridWidth)
		for (int i = 0; i < objects[0].size(); i++)
		{
			//objects[0][i]->SetPosition(xcam, ycam);
			objects[0][i]->Render();
		}
	else if (xcam < gridWidth && xcam + w > gridWidth)
	{
		for (int i = 0; i < objects[0].size(); i++)
		{
			//objects[0][i]->SetPosition(xcam, ycam);
			objects[0][i]->Render();
		}
		for (int i = 0; i < objects[1].size(); i++)
		{
			//objects[1][i]->SetPosition(xcam, ycam);
			objects[1][i]->Render();
		}
	}
	//Grid 2
	else if (xcam < gridWidth * 2  && xcam + w < gridWidth * 2)
		for (int i = 0; i < objects[1].size(); i++)
		{
			//objects[1][i]->SetPosition(xcam, ycam);
			objects[1][i]->Render();
		}
	else if (xcam < gridWidth * 2 && xcam + w > gridWidth * 2)
	{
		for (int i = 0; i < objects[1].size(); i++)
		{
			//objects[1][i]->SetPosition(xcam, ycam);
			objects[1][i]->Render();
		}
		for (int i = 0; i < objects[2].size(); i++)
		{
			//objects[2][i]->SetPosition(xcam, ycam);
			objects[2][i]->Render();
		}
	}
	//Grid 3
	else if (xcam < gridWidth * 3 && xcam + w < gridWidth * 3 )
		for (int i = 0; i < objects[2].size(); i++)
		{
			//objects[2][i]->SetPosition(xcam, ycam);
			objects[2][i]->Render();
		}
	else if (xcam < gridWidth * 3 && xcam + w > gridWidth * 3)
	{
		for (int i = 0; i < objects[2].size(); i++)
		{
			//objects[2][i]->SetPosition(xcam, ycam);
			objects[2][i]->Render();
		}
		for (int i = 0; i < objects[3].size(); i++)
		{
			//objects[3][i]->SetPosition(xcam, ycam);
			objects[3][i]->Render();
		}
	}
	//Grid 4
	else
		for (int i = 0; i < objects[3].size(); i++)
		{
			//objects[3][i]->SetPosition(xcam, ycam);
			objects[3][i]->Render();
		}

	//Render simon last to ensure that he is on the top of all objects.
	//simon->SetPosition(xcam, ycam);
	simon->Render();
}

void Grid::Update(int xcam, int ycam, int w, int h, DWORD dt)
{
	vector<LPGAMEOBJECT> temp1;

	

	for (int i = 0; i < objects[0].size(); i++)
	{
		temp1.push_back(objects[0][i]);
	}
	for (int i = 0; i < objects[1].size(); i++)
	{
		temp1.push_back(objects[1][i]);
	}
	for (int i = 0; i < objects[2].size(); i++)
	{
		temp1.push_back(objects[2][i]);
	}
	for (int i = 0; i < objects[3].size(); i++)
	{
		temp1.push_back(objects[3][i]);
	}

	if (isStopWatch)
	{
		simon->Update(dt, &objects[0]);
		return;
	}
	if (xcam < gridWidth && xcam + w  < gridWidth )
	{
		for (int i = 0; i < objects[0].size(); i++)
			objects[0][i]->Update(dt, &temp1);
		simon->Update(dt, &objects[0]);
	}

	else if (xcam < gridWidth && xcam + w >= gridWidth)
	{
		vector<LPGAMEOBJECT> temp;
		for (int i = 0; i < objects[0].size(); i++)
		{
			temp.push_back(objects[0][i]);
			objects[0][i]->Update(dt, &temp1);
		}

		for (int i = 0; i < objects[1].size(); i++)
		{
			temp.push_back(objects[1][i]);
			objects[1][i]->Update(dt, &temp1);
		}
		simon->Update(dt, &temp);

	}
	//Grid 2
	if (xcam >= gridWidth   && xcam + w < gridWidth * 2)
	{
		for (int i = 0; i < objects[1].size(); i++)
			objects[1][i]->Update(dt, &temp1);
		simon->Update(dt, &objects[1]);
	}

	else if (xcam < gridWidth * 2 && xcam + w >= gridWidth * 2)
	{
		vector<LPGAMEOBJECT> temp;
		for (int i = 0; i < objects[1].size(); i++)
		{
			temp.push_back(objects[1][i]);
			objects[1][i]->Update(dt, &temp1);
		}

		for (int i = 0; i < objects[2].size(); i++)
		{
			temp.push_back(objects[2][i]);
			objects[2][i]->Update(dt, &temp1);
		}
		simon->Update(dt, &temp);
	}
	//Grid 3
	 if (xcam >= gridWidth * 2 && xcam + w < gridWidth * 3)
	{
		for (int i = 0; i < objects[2].size(); i++)
			objects[2][i]->Update(dt, &temp1);
		simon->Update(dt, &objects[2]);
	}

	else if (xcam < gridWidth * 3 && xcam + w >= gridWidth * 3)
	{
		vector<LPGAMEOBJECT> temp;
		for (int i = 0; i < objects[2].size(); i++)
		{
			temp.push_back(objects[2][i]);
			objects[2][i]->Update(dt, &temp1);
		}

		for (int i = 0; i < objects[3].size(); i++)
		{
			temp.push_back(objects[3][i]);
			objects[3][i]->Update(dt, &temp1);
		}
		simon->Update(dt, &temp);

	}
	//Grid 4
	if(xcam >= gridWidth * 3 && xcam  < gridWidth * 4)
	{
		for (int i = 0; i < objects[3].size(); i++)
			objects[3][i]->Update(dt, &temp1);
		simon->Update(dt, &objects[3]);
	}
	
}



void Grid::Clear()
{
	delete objects;
}

void Grid::DeleteEnable()
{


	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < objects[i].size(); j++)
		{
			if (objects[i][j]->isEnable == false)
			{
				if (objects[i][j]->isDropItem == true)
				{
					Items *item = new Items();
					item->LoadResources();
					if (simon->checkWhip())
						item->setLv2();
					item->Random();
					item->isEffect = false;
					item->SetPosition(objects[i][j]->x, objects[i][j]->y);
					AddObject(item);
				}
				if (objects[i][j]->isEffect == true)
				{
					EffectDead *effect = new EffectDead();
					effect->LoadResources();
					effect->SetPosition(objects[i][j]->x, objects[i][j]->y);
					effect->isEffect = false;
					AddObject(effect);

					effect = new EffectDead();
					effect->LoadResources();
					effect->state = 1;
					effect->SetPosition(objects[i][j]->x , objects[i][j]->y);
					effect->isEffect = false;
					AddObject(effect);
				}
				objects[i].erase(objects[i].begin() + j);
				
			}


		}
	}
}
