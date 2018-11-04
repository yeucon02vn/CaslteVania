#pragma once
#pragma once
#define SAFE_DELETE(p) {if(p) { delete(p); p = NULL;} } 
#define CLASS_NAME	"Castle Vania"
#define FULLSCREEN	false
#define GAME_TITLE	"Castle Vania"
#define GAME_WIDTH	640
#define GAME_HEIGHT	480
#define FRAME_RATE			30
#define FPS					60
#define MAX_TIME_PER_FRAME	1000 / FPS
#define GAME_FONT			"Resource\\font\\prstart.ttf"
#define TITLE_SCREEN		"Resource\\sprites\\TITLE_SCREEN.bmp"
#define TITLE_ANIMATION		"Resource\\sprites\\TitleAnimation.png"
#define SIMON_SPRITE		"Resource\\sprites\\Simon\\Simon_ver_editted.png"
#define WHIP_SPRITE			"Resource\\sprites\\Weapons\\WHIP.png"
#define DEAD_SPRITE				"Resource\\sprites\\Effect\\DEAD.png"
#define COLLIDE_EFFECT_SPRITE	"Resource\\sprites\\Effect\\0.png"
#define CASTLE_SPRITE		"Resource\\sprites\\Castle-lv1.png"
#define LEVEL_ONE_BG		"Resource\\sprites\\lv1.s"
#define	LEVEL_ONE_MATRIX_BG	"Resource\\sprites\\lv1.b"
#define GROUND_TEST		"Resource\\sprites\\ground_test.png"
// Animations' status
#define STAND				0
#define MOVE				1
#define	SIT					2
#define JUMP				3
#define HIT_STAND			4
#define HIT_SIT				5
#define FALL_DOWN			6
#define HURTED				9
#define FIGHT				12
#define THROW_SUB_WEAPON	13
#define DEAD				16
#define INVISIBLE			17
#define EAT_ITEM			18
#define STAND_BACK			19
#define JUMP_FORCE		570
#define GRAVITY			800
#define SPEED			150
#define MAX_VELOCITY	200
#define EARTH_ACCELERATION -2000
#define SIDE_ABOVE		1.0f
#define SIDE_BOTTOM		-1.0f
#define SIDE_LEFT		-1.0f
#define SIDE_RIGHT		1.0f
#define TAG_NULL				-100
#define TAG_CANDLE				11
#define TAG_GROUND				12
#define TAG_SIMON			31
#define TAG_WHIP			35
#define	GAME_PLAY_STATE_ONE		1

