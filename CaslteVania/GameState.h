#pragma once
#include "Camera.h"
#include <fstream>
#include <vector>
#include "Graphics.h"
#include "QuadTree.h"
#include "Simon.h"


class GameState
{
	float simonDeadTime = 1.5;
protected:

	Camera *cam;
	std::vector<GameObject*> *listObject;
	bool changeState;
	float time;
	D3DXVECTOR3 simonCheckpoint;
	D3DXVECTOR3 cameraCheckpoint;
	bool canUseKeyboard;
	static Simon* simon;

	float timeKillAll;
	bool choose;
	Graphics *graphics;    
public:
	int state;
	GameState() {}
	~GameState() {}
	virtual bool Initialize(Graphics *graphics) = 0;
	virtual void Render() {};
	virtual void Update(float gameTime) = 0;
	virtual void DestroyAll() = 0;

	/*
	* 2 cai nay dung de chuyen scene
	*/
	virtual bool GetChangingState() { return changeState; };
	virtual void SetChangingState(bool status) { changeState = status; }

	virtual bool CameraFollowHandle(float gameTime) = 0;
};

