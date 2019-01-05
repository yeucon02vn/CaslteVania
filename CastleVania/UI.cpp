#include "UI.h"

UI::UI()
{
}

UI::~UI()
{
}

void UI::LoadResources()
{
	Sprites * sprites = Sprites::GetInstance();
	LPANIMATION ani;
	Textures * textures = Textures::GetInstance();


	textures->Add(ID_TEX_BLACKBOARD, L"Resource\\sprites\\UI\\blackboard.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_BOSSHP, L"Resource\\sprites\\UI\\EnemyHP.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_NOHP, L"Resource\\sprites\\UI\\NoHP.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_HP, L"Resource\\sprites\\UI\\HP.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_KNIFE_L, KNIFE_L_SPRITE, D3DCOLOR_XRGB(255, 0, 255));

	textures->Add(ID_TEX_ITEM_AXE, L"Resource\\sprites\\Sub_weapons\\AXE.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_CROSS, L"Resource\\sprites\\Sub_weapons\\CROSS.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_HOLYWATER, L"Resource\\sprites\\Sub_weapons\\HOLY_WATER.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_STOP_WATCH, L"Resource\\sprites\\Sub_weapons\\STOP_WATCH.png", D3DCOLOR_XRGB(255, 255, 255));

	textures->Add(ID_TEX_DOUBLE_SHOT_UI, L"Resource\\sprites\\UI\\DOUBLE_SHOOT_UI.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_TRIPLE_SHOT_UI, L"Resource\\sprites\\UI\\TRIPLE_SHOOT_UI.png", D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 texBoard = textures->Get(ID_TEX_BLACKBOARD);
	LPDIRECT3DTEXTURE9 texBosshp = textures->Get(ID_TEX_BOSSHP);
	LPDIRECT3DTEXTURE9 texSimonhp = textures->Get(ID_TEX_HP);
	LPDIRECT3DTEXTURE9 texNohp = textures->Get(ID_TEX_NOHP);
	LPDIRECT3DTEXTURE9 texKnifeL = textures->Get(ID_TEX_KNIFE_L);

	LPDIRECT3DTEXTURE9 texAxe = textures->Get(ID_TEX_ITEM_AXE);
	LPDIRECT3DTEXTURE9 texCross = textures->Get(ID_TEX_ITEM_CROSS);
	LPDIRECT3DTEXTURE9 texHolyWater = textures->Get(ID_TEX_HOLYWATER);
	LPDIRECT3DTEXTURE9 texStopWatch = textures->Get(ID_TEX_STOP_WATCH);

	LPDIRECT3DTEXTURE9 texDouble = textures->Get(ID_TEX_DOUBLE_SHOT_UI);
	LPDIRECT3DTEXTURE9 texTriple = textures->Get(ID_TEX_TRIPLE_SHOT_UI);

	sprites->Add(210001, 0, 0, 125, 59, texBoard);		// walk
	sprites->Add(210002, 0, 0, 10, 20, texBosshp);
	sprites->Add(210003, 0, 0, 10, 20, texSimonhp);
	sprites->Add(210004, 0, 0, 10, 20, texNohp);
	sprites->Add(210005, 0, 0, 32, 18, texKnifeL);

	sprites->Add(210006, 0, 0, 30, 28, texAxe);
	sprites->Add(210007, 0, 0, 30, 28, texCross);
	sprites->Add(210008, 0, 0, 32, 32, texHolyWater);
	sprites->Add(210009, 0, 0, 30, 32, texStopWatch);

	sprites->Add(210010, 0, 0, 42, 42, texDouble);
	sprites->Add(210011, 0, 0, 42, 42, texTriple);

	ani = new Animation(100);	// board
	ani->Add(210001);
	sprite.push_back(ani);

	ani = new Animation(100);	// boss hp
	ani->Add(210002);
	sprite.push_back(ani);

	ani = new Animation(100);	// simon hp
	ani->Add(210003);
	sprite.push_back(ani);

	ani = new Animation(100);	// no hp
	ani->Add(210004);
	//animations->Add(2104, ani);
	sprite.push_back(ani);
	
	ani = new Animation(100);	// knife
	ani->Add(210005);
	sprite.push_back(ani);

	ani = new Animation(100);	// axe
	ani->Add(210006);
	sprite.push_back(ani);

	ani = new Animation(100);	// cross
	ani->Add(210007);
	sprite.push_back(ani);

	ani = new Animation(100);	// holywater
	ani->Add(210008);
	sprite.push_back(ani);

	ani = new Animation(100);	// stop watch
	ani->Add(210009);
	sprite.push_back(ani);

	ani = new Animation(100);	// stop watch
	ani->Add(210010);
	sprite.push_back(ani);

	ani = new Animation(100);	// stop watch
	ani->Add(210011);
	sprite.push_back(ani);

	font = NULL;
	AddFontResourceEx(GAME_FONT, FR_PRIVATE, NULL);
	HRESULT result = D3DXCreateFont(
	d3ddv, 20, 0, FW_NORMAL, 1, false,
	DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
	ANTIALIASED_QUALITY, FF_DONTCARE, L"Press Start", &font);

	DebugOut(L"%d", result);

	SetRect(&rect, 0, 20, SCREEN_WIDTH, SCREEN_HEIGHT);
	information = "SCORE_000000 TIME 0000 STAGE 00\n";
	information += "PLAYER                =62\n";
	information += "ENEMY                P=3\n";
}

void UI::Update(int bossHP, int time, int life, int stage)
{
	this->bossHP = bossHP;
	this->time = time;
	this->stage = stage;


	std::string scoreString = std::to_string(simon->getScore());
	while (scoreString.length() < 6)
		scoreString = "0" + scoreString;


	std::string timeString = std::to_string(this->time);
	while (timeString.length() < 4)
		timeString = "0" + timeString;

	std::string stageString = std::to_string(this->stage);
	while (stageString.length() < 2)
		stageString = "0" + stageString;


	information = "SCORE_" + scoreString + " TIME " +  timeString + " STAGE " + stageString + "\n";
	information += "PLAYER                 " + std::to_string(simon->getHeart()) + "\n";
	information += "ENEMY                  " + std::to_string(simon->getLife()) + "\n";
}

void UI::Render()
{
	sprite[0]->DrawBoard(330, 42);
	
	if (font)
		font->DrawTextA(NULL, information.c_str(), -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));

	for(int i =0; i < 16; i++)
		if(i < simon->GetHP())
			sprite[2]->DrawBoard(130 + 12 *i , 42);
		else
			sprite[3]->DrawBoard(130 + 12 * i, 42);

	for (int i = 0; i < 16; i++)
		if (i < bossHP)
			sprite[1]->DrawBoard(130 + 12 * i, 68);
		else
			sprite[3]->DrawBoard(130 + 12 * i, 68);
	if(simon->currentItem == ITEM_ANI_KNIFE)
		sprite[4]->DrawBoard(348, 60);
	else if (simon->currentItem == ITEM_ANI_AXE)
		sprite[5]->DrawBoard(348, 60);
	else if (simon->currentItem == ITEM_ANI_CROSS)
		sprite[6]->DrawBoard(348, 60);
	else if (simon->currentItem == ITEM_ANI_HOLYWATER)
		sprite[7]->DrawBoard(348, 60);
	else if (simon->currentItem == ITEM_ANI_STOPWATCH)
		sprite[8]->DrawBoard(348, 60);
	if (simon->updateDame == ITEM_ANI_DOUBLE)
		sprite[9]->DrawBoard(520,60);
	else if (simon->updateDame == ITEM_ANI_TRIPLE)
	{
		sprite[10]->DrawBoard(520,60);
	}



}
