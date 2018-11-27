#include "Whip.h"

void Whip::LoadResources()
{
	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();
	LPANIMATION ani;
	Textures * textures = Textures::GetInstance();
	textures->Add(ID_TEX_WHIPR, WHIP_R_SPRITE, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_WHIPL, WHIP_L_SPRITE, D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texWhipR = textures->Get(ID_TEX_WHIPR);
	LPDIRECT3DTEXTURE9 texWhipL = textures->Get(ID_TEX_WHIPL);
#pragma region  Whip Right
#pragma region Normal Whip
	sprites->Add(20001, 480, 0, 720, 66, texWhipR);
	sprites->Add(20002, 240, 0, 480, 66, texWhipR);
	sprites->Add(20003, 0, 0, 240, 66, texWhipR);
#pragma endregion

#pragma region Lv1 Whip
	sprites->Add(20011, 480, 66, 720, 132, texWhipR);
	sprites->Add(20012, 240, 66, 480, 132, texWhipR);
	sprites->Add(20013, 0, 66, 240, 132, texWhipR);
#pragma endregion

#pragma region Lv2 Whip
	sprites->Add(20021, 0, 132, 240, 198, texWhipR);
	sprites->Add(20022, 240, 132, 480, 198, texWhipR);
	sprites->Add(20023, 480, 132, 720, 198, texWhipR);
	sprites->Add(20024, 480, 198, 720, 264, texWhipR);
	sprites->Add(20025, 240, 198, 480, 264, texWhipR);
	sprites->Add(20026, 0, 198, 240, 264, texWhipR);
	sprites->Add(20027, 480, 264, 720, 330, texWhipR);
	sprites->Add(20028, 240, 264, 480, 330, texWhipR);
	sprites->Add(20029, 0, 264, 240, 330, texWhipR);
	sprites->Add(20030, 480, 330, 720, 396, texWhipR);
	sprites->Add(20031, 240, 330, 480, 396, texWhipR);
	sprites->Add(20032, 0, 330, 240, 396, texWhipR);
#pragma endregion

#pragma endregion


	
#pragma region Whip Left
#pragma region Normal Whip
	sprites->Add(21001, 0, 0, 240, 66, texWhipL);
	sprites->Add(21002, 240, 0, 480, 66, texWhipL);
	sprites->Add(21003, 480, 0, 720, 66, texWhipL);
#pragma endregion

#pragma region Lv1 Whip
	sprites->Add(21011, 0, 66, 240, 132, texWhipL);
	sprites->Add(21012, 240, 66, 480, 132, texWhipL);
	sprites->Add(21013, 480, 66, 720, 132, texWhipL);
#pragma endregion

#pragma region Lv2 Whip
	sprites->Add(21021, 0, 132, 240, 198, texWhipL);
	sprites->Add(21022, 240, 132, 480, 198, texWhipL);
	sprites->Add(21023, 480, 132, 720, 198, texWhipL);
	sprites->Add(21024, 0, 198, 240, 264, texWhipL);
	sprites->Add(21025, 240, 198, 480, 264, texWhipL);
	sprites->Add(21026, 480, 198, 720, 264, texWhipL);
	sprites->Add(21027, 0, 264, 240, 330, texWhipL);
	sprites->Add(21028, 240, 264, 480, 330, texWhipL);
	sprites->Add(21029, 480, 264, 720, 330, texWhipL);
	sprites->Add(21030, 0, 330, 240, 396, texWhipL);
	sprites->Add(21031, 240, 330, 480, 396, texWhipL);
	sprites->Add(21032, 480, 330, 720, 396, texWhipL);
#pragma endregion


#pragma endregion


	
#pragma region Add animations right
	
	ani = new Animation(100); // normal
	ani->Add(20001);
	ani->Add(20002);
	ani->Add(20003);
	animations->Add(201, ani);

	ani = new Animation(100); // lv1
	ani->Add(20011);
	ani->Add(20012);
	ani->Add(20013);
	animations->Add(202, ani);

	ani = new Animation(25); // lv2 
	ani->Add(20021);
	ani->Add(20022);
	ani->Add(20023);
	ani->Add(20024);
	ani->Add(20025);
	ani->Add(20026);
	ani->Add(20027);
	ani->Add(20028);
	ani->Add(20029);
	ani->Add(20030);
	ani->Add(20031);
	ani->Add(20032);
	animations->Add(203, ani);
#pragma endregion

	
#pragma region Add animations left
	ani = new Animation(100);
	ani->Add(21001);
	ani->Add(21002);
	ani->Add(21003);
	animations->Add(211, ani);

	ani = new Animation(100);
	ani->Add(21011);
	ani->Add(21012);
	ani->Add(21013);
	animations->Add(212, ani);

	ani = new Animation(25);
	ani->Add(21021);
	ani->Add(21022);
	ani->Add(21023);
	ani->Add(21024);
	ani->Add(21025);
	ani->Add(21026);
	ani->Add(21027);
	ani->Add(21028);
	ani->Add(21029);
	ani->Add(21030);
	ani->Add(21031);
	ani->Add(21032);
	animations->Add(213, ani);

#pragma endregion

	

	AddAnimation(201);
	AddAnimation(202);
	AddAnimation(203);
	AddAnimation(211);
	AddAnimation(212);
	AddAnimation(213);
	type = WHIP_NORMAL;

}

void Whip::Update()
{
}

void Whip::Render()
{
	if (type == WHIP_NORMAL)
	{
		if (nx > 0)
			action = WHIP_ANI_NORMAL_RIGHT;
		else
			action = WHIP_ANI_NORMAL_LEFT;
	}
	else if (type == WHIP_LV1)
	{
		if (nx > 0)
			action = WHIP_ANI_LV1_RIGHT;
		else
			action = WHIP_ANI_LV1_LEFT;
	}
	else
	{
		if (nx > 0)
			action = WHIP_ANI_LV2_RIGHT;
		else
			action = WHIP_ANI_LV2_LEFT;
	}
	animations[action]->Render(x, y);
}

void Whip::SetWhipPosition(float x, float y , bool isSit)
{

		if (isSit == true)
			y += 15.0f;

		x -= 90.0f;
		y += 1.0f;

		SetPosition(x, y);


}

bool Whip::CheckCollision(float obj_left, float obj_top, float obj_right, float obj_bottom)
{
	float whip_left,
		whip_top,
		whip_right,
		whip_bottom;

	GetBoundingBox(whip_left, whip_top, whip_right, whip_bottom);
	return AABB(whip_left, whip_top, whip_right, whip_bottom, obj_left, obj_top, obj_right, obj_bottom);
}

void Whip::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	top = y + 15;
	bottom = top + WHIP_BBOX_HEIGHT;
	if (type == WHIP_LV2)
	{
		if (nx < 0)
		{
			left = x + 20;
			right = left + WHIP_BBOX_WIDTH + 30;
		}
		else if (nx > 0)
		{
			left = x + 150;
			right = left + WHIP_BBOX_WIDTH + 30;
		}
	}
	else
	{
		if (nx < 0)
		{
			left = x + 50;
			right = left + WHIP_BBOX_WIDTH;
		}
		else if (nx > 0)
		{
			left = x + 150;
			right = left + WHIP_BBOX_WIDTH;
		}
	}
}

void Whip::reset()
{
	animations[action]->setCurrentFrame(-1);
}

