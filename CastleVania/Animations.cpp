#include "Animations.h"
#include "Game.h"
#include "debug.h"

void Animation::Add(int spriteId, DWORD time)
{
	if (time == 0) time = this->defaultTime;

	LPSPRITE sprite = Sprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new AnimationFrame(sprite, time);
	frames.push_back(frame);
}

void Animation::Render(float x, float y, int alpha)
{
	DWORD now = GetTickCount();

	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime >= t ) //  
		{
			currentFrame++;
			lastFrameTime = now;

			if (currentFrame == frames.size())
			{
				currentFrame = 0;
			}
		}

	}
	frames[currentFrame]->GetSprite()->Draw(x, y, alpha);
}



void Animation::setCurrentFrame(int frame)
{
	this->currentFrame = frame;
}

int Animation::getCurrentFrame()
{
	return currentFrame;
}

int Animation::getLastFrame()
{
	return frames.size() -1;
}

//void Animation::Draw(float x, float y, Camera * cam, int alpha)
//{
//	DWORD now = GetTickCount();
//	if (currentFrame == -1)
//	{
//		currentFrame = 0;
//		lastFrameTime = now;
//	}
//	else
//	{
//		DWORD t = frames[currentFrame]->GetTime();
//		if (now - lastFrameTime >= t)
//		{
//			currentFrame++;
//			lastFrameTime = now;
//
//
//			if (currentFrame == frames.size())
//			{
//				currentFrame = 0;
//			}
//		}
//
//	}
//	frames[currentFrame]->GetSprite()->DrawCamera(x, y,cam, alpha);
//}

void Animation::Draw(int x, int y)
{						
	frames[currentFrame]->GetSprite()->Draw(x, y ,255);
}


Animations * Animations::__instance = NULL;

Animations * Animations::GetInstance()
{
	if (__instance == NULL) __instance = new Animations();
	return __instance;
}

void Animations::Add(int id, LPANIMATION ani)
{
	animations[id] = ani;
}

LPANIMATION Animations::Get(int id)
{
	return animations[id];
}

