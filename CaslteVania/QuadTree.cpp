#include "QuadTree.h"

QuadTree::QuadTree(LPDIRECT3DDEVICE9 gDevice, Camera *cam)
{
	this->node = NULL;
	this->gDevice = gDevice;
	this->cam = cam;
	this->region = new RECT();
}

QuadTree::~QuadTree(void)
{
	for (std::vector<GameObject*>::iterator i = listObject->begin(); i != listObject->end(); i++)
	{
		delete[](*i);
	}

	delete[] listObject;
}

std::map<int, GameObject*> QuadTree::mapObject;

void QuadTree::Load(std::string file)
{
	std::ifstream input;
	input.open(file, std::ifstream::in);

	std::string checkEnd;
	std::string trace;

	int id;
	int type;
	float x;
	float y;
	int width;
	int height;

	float left;
	float top;
	float right;
	float bottom;
	int n;
	int objectID;

	int count = 0;

	while (input >> checkEnd)
	{
		if (checkEnd == "END")
		{
			count++;
			continue;
		}

		if (count == 0)
		{
			id = atoi(checkEnd.c_str());
			input >> type >> x >> y >> width >> height;
			LoadObject(id, type, x, y, width, height);
		}
		else if (count == 1)
		{
			id = atoi(checkEnd.c_str());
			input >> left >> top >> right >> bottom >> n;

			std::vector<GameObject*>* list = new std::vector<GameObject*>();
			for (int i = 0; i < n; i++)
			{
				input >> objectID;
				list->push_back(mapObject[objectID]);
			}

			trace.clear();

			while (true)
			{
				id--;
				if (id < 0)
					break;
				else
				{
					trace = std::to_string(id % 4) + trace;
					id = id / 4;
				}
			}

			trace = trace + "e";

			LoadQuad(trace, 0, left, top, right, bottom, list);
		}
	}
}

void QuadTree::LoadQuad(std::string trace, int pos, float left, float top, float right, float bottom, std::vector<GameObject*> *list)
{
	if (trace[pos] == 'e')
	{
		SetRect(this->region, left, top, right, bottom);
		this->listObject = list;
	}
	else
	{
		if (!this->node)
		{
			node = new QuadTree*[4];
			node[0] = new QuadTree(gDevice, cam);
			node[1] = new QuadTree(gDevice, cam);
			node[2] = new QuadTree(gDevice, cam);
			node[3] = new QuadTree(gDevice, cam);
		}

		if (trace[pos] == '0')
			node[0]->LoadQuad(trace, pos + 1, left, top, right, bottom, list);
		else if (trace[pos] == '1')
			node[1]->LoadQuad(trace, pos + 1, left, top, right, bottom, list);
		else if (trace[pos] == '2')
			node[2]->LoadQuad(trace, pos + 1, left, top, right, bottom, list);
		else if (trace[pos] == '3')
			node[3]->LoadQuad(trace, pos + 1, left, top, right, bottom, list);
	}
}

void QuadTree::LoadObject(int id, int type, float x, float y, int width, int height)
{
	if (type == 10)
	{
		GameObject *object;
		object = new Candle();
		object->Initialize(gDevice, "Resource\\sprites\\Ground\\0.png", x, y, type);
		object->SetID(id);
		object->SetSize(width, height);
		object->SetRegion(0, width, 0, -height);
		mapObject[id] = object;
	}
	else if (type == TAG_GROUND)
	{
		GameObject *object;
		object = new Ground(width, height);
		object->Initialize(gDevice, "Resource\\sprites\\Ground\\2.png", x, y, TAG_GROUND);
		object->SetID(id);
		object->SetSize(width, height);
		object->SetRegion(0, width, 0, -height);
		object->SetBox(x, y, width, height, 0.0f, 0.0f);
		mapObject[id] = object;
	}

}

void QuadTree::Remove(GameObject* object)
{
	if (this->node)
	{
		if (this->node[0]->IsContain(object))
			this->node[0]->Remove(object);

		if (this->node[1]->IsContain(object))
			this->node[1]->Remove(object);

		if (this->node[2]->IsContain(object))
			this->node[2]->Remove(object);

		if (this->node[3]->IsContain(object))
			this->node[3]->Remove(object);
	}
	else if (this->IsContain(object))
	{
		for (std::vector<GameObject*>::iterator i = this->listObject->begin(); i != this->listObject->end(); i++)
		{
			if ((*i) == object)
			{
				this->listObject->erase(i);
				break;
			}
		}
	}
}

void QuadTree::Update(float gameTime)
{
	for (std::vector<GameObject*>::iterator i = listObject->begin(); i != listObject->end(); i++)
	{
		(*i)->Update(gameTime);
	}

}

void QuadTree::Render()
{
	for (std::vector<GameObject*>::iterator i = listObject->begin(); i != listObject->end(); i++)
	{
		if ((*i)->IsEnable())
			(*i)->Render(this->cam);
	}
}


bool QuadTree::IsContain(GameObject *object)
{
	return object->IsInRegion(this->region);
}

bool QuadTree::IsContain(RECT *region)
{
	if (this->region->right < region->left || this->region->left > region->right ||
		this->region->bottom > region->top || this->region->top < region->bottom)
		return false;
	return true;
}




void QuadTree::GetObjectList(std::vector<GameObject*> *returnList, RECT *region)
{
	if (this->node)
	{
		if (this->node[0]->IsContain(region))
			this->node[0]->GetObjectList(returnList, region);

		if (this->node[1]->IsContain(region))
			this->node[1]->GetObjectList(returnList, region);

		if (this->node[2]->IsContain(region))
			this->node[2]->GetObjectList(returnList, region);

		if (this->node[3]->IsContain(region))
			this->node[3]->GetObjectList(returnList, region);
	}
	else if (this->IsContain(region))
	{
		for (std::vector<GameObject*>::iterator i = this->listObject->begin(); i != this->listObject->end(); i++)	
			returnList->push_back(*i);

	}
}