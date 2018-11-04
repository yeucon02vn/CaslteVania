#pragma once
#include "Camera.h"
#include <d3d9.h>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include "Candle.h"
#include "Ground.h"



#define MAX_OBJECT_IN_REGION 1
#define MAX_LEVEL 2

class QuadTree
{
protected:
	LPDIRECT3DDEVICE9 gDevice;
	Camera* cam;
	std::vector<GameObject*> *listObject;

	//////////////////////////////////
	int id;
	RECT* region;
	QuadTree** node;

public:
	static std::map<int, GameObject*> mapObject;

	QuadTree(LPDIRECT3DDEVICE9 gDevice, Camera *cam);
	~QuadTree(void);

	void Load(std::string file);
	void LoadQuad(std::string trace, int pos, float left, float top, float right, float bottom, std::vector<GameObject*> *list);
	void LoadObject(int id, int type, float x, float y, int width, int height);

	void Update(float gameTime);
	void Render();

	std::vector<GameObject*> *GetListObject() { return listObject; }


	//////////////////////////////////////////////////////////////////////////////////////////
	void Remove(GameObject* object);
	bool IsContain(GameObject *object);
	bool IsContain(RECT *region);
	void GetObjectList(std::vector<GameObject*> *returnList, RECT *region);
};
