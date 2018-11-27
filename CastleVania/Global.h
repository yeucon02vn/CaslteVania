#pragma once

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define DIRECTINPUT_VERSION 0x0800

#define KEYBOARD_BUFFER_SIZE 1024	
#define WINDOW_CLASS_NAME	L"Castle Vania"
#define FULLSCREEN	false
#define MAIN_WINDOW_TITLE	L"Castle Vania"
#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

#define FPS					120

#define MAX_TIME_PER_FRAME		(DWORD)1000 / FPS
#define TITLE_SCREEN			L"Resource\\sprites\\TITLE_SCREEN.bmp"
#define TITLE_ANIMATION			L"Resource\\sprites\\TitleAnimation.png"
#define SIMON_L_SPRITE			L"Resource\\sprites\\Simon\\SIMONL.png"
#define SIMON_R_SPRITE			L"Resource\\sprites\\Simon\\SIMONR.png"
#define WHIP_R_SPRITE			L"Resource\\sprites\\Weapons\\WHIPR.png"
#define WHIP_L_SPRITE			L"Resource\\sprites\\Weapons\\WHIPL.png"
#define COLLIDE_EFFECT_SPRITE	L"Resource\\sprites\\Effect\\0.png"
#define CASTLE_SPRITE			L"Resource\\sprites\\Castle-lv1.png"
#define BBOX_SPRITE				L"Resource\\sprites\\Ground\\bbox.png"

#define BIG_HEART_SPRITE		L"Resource\\sprites\\Items\\BIG_HEART.png"
#define MORNING_STAR_SPRITE		L"Resource\\sprites\\Items\\MORNING_STAR.png"
#define KNIFE_SPRITE			L"Resource\\sprites\\Sub_weapons\\KNIFE.png"
#define KNIFE_L_SPRITE			L"Resource\\sprites\\Sub_weapons\\KNIFEL.png"


#define ID_TEX_BBOX -100	
#define	ID_LEVEL_ONE_MATRIX_BG	 0
#define ID_TEX_SIMONR 101
#define ID_TEX_SIMONL 102
#define ID_TEX_WHIPR 201
#define ID_TEX_WHIPL 202
#define ID_TEX_EFFECT 301
#define ID_TEX_LCANDLE 401
#define ID_TEX_GROUND 501
#define ID_TEX_MORNING_STAR 601
#define ID_TEX_BIG_HEART 701
#define ID_TEX_KNIFE 801
#define ID_TEX_KNIFE_L 802

// Animations' status

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALK			100
#define SIMON_STATE_JUMP			200
#define SIMON_STATE_SIT				300
#define SIMON_STATE_ATK				400
#define SIMON_STATE_S_ATK			500
#define SIMON_STATE_DIE				900


#define GRAVITY						0.002f
#define SIMON_WALKING_SPEED			0.1f 
#define SIMON_JUMP_SPEED_Y			0.5f
#define SIMON_JUMP_DEFLECT_SPEED	0.2f
#define SIMON_DIE_DEFLECT_SPEED		0.5f
#define ITEM_FALLING_SPEED			0.1f
#define ITEM_Knife_SPEED			0.2f 


#define GROUND_WIDTH				32
#define GROUND_HEIGHT				32
#define LCANDLE_WIDTH				32
#define LCANDLE_HEIGHT				64
#define SIMON_BBOX_WIDTH			40
#define SIMON_BBOX_HEIGHT			60
#define WHIP_BBOX_HEIGHT			20
#define WHIP_BBOX_WIDTH				40
#define BIG_HEART_BBOX_WIDTH		24
#define	BIG_HEART_BBOX_HEIGHT		20
#define MORNING_STAR_BBOX_WIDTH		32
#define MORNING_STAR_BBOX_HEIGHT	32
#define KNIFE_BBOX_WIDTH	        32
#define KNIFE_BBOX_HEIGHT			18


#define SIMON_ANI_IDLE_RIGHT		0
#define SIMON_ANI_IDLE_LEFT			1
#define SIMON_ANI_WALKING_RIGHT		2
#define SIMON_ANI_WALKING_LEFT		3
#define SIMON_ANI_SIT_RIGHT			4	
#define SIMON_ANI_SIT_LEFT			5
#define SIMON_ANI_ATK_RIGHT			6
#define SIMON_ANI_ATK_LEFT			7
#define SIMON_ANI_S_ATK_RIGHT		8
#define SIMON_ANI_S_ATK_LEFT		9
#define SIMON_ANI_JUMP_RIGHT		10
#define SIMON_ANI_JUMP_LEFT			11
#define SIMON_ANI_DIE				99
#define SIMON_STATE_USE_ITEM		12

#define WHIP_ANI_NORMAL_RIGHT			0
#define WHIP_ANI_LV1_RIGHT				1
#define WHIP_ANI_LV2_RIGHT				2
#define WHIP_ANI_NORMAL_LEFT			3
#define WHIP_ANI_LV1_LEFT				4
#define WHIP_ANI_LV2_LEFT				5
 
#define ITEM_ANI_BIG_HERT		 		0
#define ITEM_ANI_WHIP					1
#define ITEM_ANI_KNIFE			2


#define SIMON_ATTACK_TIME			320
#define SIMON_UNTOUCHABLE_TIME		5000
#define ITEM_TIME_DESTROYED         5000

#define WHIP_NORMAL 0
#define WHIP_LV1	1
#define WHIP_LV2	2