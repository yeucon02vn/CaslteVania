#pragma once
#include "Sprites.h"
class AnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	AnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return this->time; }
	LPSPRITE GetSprite() { return this->sprite; }
};

typedef AnimationFrame *LPANIMATION_FRAME;

class Animation
{
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
public:
	Animation(int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(int spriteId, DWORD time = 0);
	void setCurrentFrame(int frame);
	int getCurrentFrame();
	int getLastFrame();
	//void Draw(float x, float y, Camera *cam, int alpha = 255);
	void Render(float x, float y, int alpha = 255);
	void Draw(int x, int y);

};

typedef Animation *LPANIMATION;

class Animations
{
	static Animations * __instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);

	static Animations * GetInstance();
};