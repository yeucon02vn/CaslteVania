#include "GameState2.h"


GameState2::GameState2()
{
	LoadResources();
}


GameState2::~GameState2()
{
}


void GameState2::LoadResources()
{
	tileMap = new TileMap(STATE_LV2);

	grid = grid->GetInstance();
	grid->GetMapSize(6000, 960);

	door = new Door();
	door->LoadResources();

	door2 = new Door();
	door2->LoadResources();

	ground = new Ground();
	ground->LoadResources();

	stair = new Stair();
	stair->LoadResources();




	changeState = false;

	simon->SetPosition(20, 380);
	D3DXVECTOR2 point;
	point.x = 115;
	point.y = 0;
	simon->setCheckPoint(point);

	objects.push_back(simon);
	grid->AddSimon(simon);




#pragma region Tạo cửa


	door->AddAnimation(304);
	door->SetPosition(3049, 162);
	objects.push_back(door);
	grid->AddObject(door);


	door2->AddAnimation(304);
	door2->SetPosition(5616, 289);
	objects.push_back(door2);
	grid->AddObject(door2);
#pragma endregion

	for (int i = 0; i < 3; i++)
	{
		panther[i] = new Panther();
		panther[i]->LoadResources();
	}

	panther[0]->setNx(-1);
	panther[0]->SetPosition(1440, 260);
	panther[0]->setPre(1440, 260);
	objects.push_back(panther[0]);
	grid->AddObject(panther[0]);

	panther[1]->setNx(-1);
	panther[1]->state = 1;
	panther[1]->SetPosition(1600, 195);
	panther[1]->setPre(1600, 195);
	objects.push_back(panther[1]);
	grid->AddObject(panther[1]);

	panther[2]->setNx(-1);
	panther[2]->SetPosition(1900, 260);
	panther[2]->setPre(1900, 260);
	objects.push_back(panther[2]);
	grid->AddObject(panther[2]);

	boss = new Boss(16,2,1000);
	boss->LoadResources();
	boss->setPoisitionBoss(5307, 130); //5307
	objects.push_back(boss);
	grid->AddObject(boss);

	for (int i = 0; i < 4; i++)
	{
		merman[i] = new Merman();
		merman[i]->LoadResources();
		merman[i]->setNx(1);
	}
	
	merman[0]->SetPosition(3750, 964);
	merman[0]->setPre(3750, 964);
	grid->AddObject(merman[0]);
	
	merman[1]->SetPosition(3850, 964);
	merman[1]->setPre(3850, 964);
	grid->AddObject(merman[1]);

	merman[2]->SetPosition(3450, 964);
	merman[2]->setPre(3450, 964);
	grid->AddObject(merman[2]);

	merman[3]->SetPosition(3300, 964);
	merman[3]->setPre(3300, 964);
	grid->AddObject(merman[3]);

	for (int i = 0; i < 2; i++)
	{
		bats[i] = new Bat();
		bats[i]->LoadResources();
		bats[i]->isDropItem = true;
		bats[i]->setNx(-1);
	}
	
	bats[0]->SetPosition(3600, 250);
	bats[0]->setPre(3600, 250);
	bats[0]->SetState(1);
	objects.push_back(bats[0]);
	grid->AddObject(bats[0]);

	bats[1]->SetPosition(4400, 200);
	bats[1]->setPre(4400, 200);
	bats[1]->SetState(1);
	objects.push_back(bats[1]);
	grid->AddObject(bats[1]);

	for (int i = 0; i < 3; i++)
	{
		zombies[i] = new Zombie();
		zombies[i]->LoadResources();
		zombies[i]->setNx(-1);
		zombies[i]->SetPosition(900 + i*50, 370);
		zombies[i]->setPre(900 + i * 50, 370);
		zombies[i]->SetState(2);
		objects.push_back(zombies[i]);
		grid->AddObject(zombies[i]);
	}

	for (int i = 0; i < 3; i++)
	{
		zombies[3+i] = new Zombie();
		zombies[3+i]->LoadResources();
		zombies[3+i]->setNx(-1);
		zombies[3+i]->SetPosition(2500 + i * 50, 370);
		zombies[3 + i]->setPre(2500 + i * 50, 370);
		zombies[3+i]->SetState(2);
		objects.push_back(zombies[3+i]);
		grid->AddObject(zombies[3+i]);
	}

	for (int i = 0; i < 3; i++)
	{
		zombies[6 + i] = new Zombie();
		zombies[6 + i]->LoadResources();
		zombies[6 + i]->setNx(-1);
		zombies[6 + i]->SetPosition(4800 + i * 50, 370);
		zombies[6 + i]->setPre(4800 + i * 50, 370);
		zombies[6 + i]->SetState(2);
		objects.push_back(zombies[6 + i]);
		grid->AddObject(zombies[6+ i]);
	}

#pragma region Tạo gạch
	for (int i = 0; i < 99; i++) // tạo gạch tới trước cầu thang xuống 1
	{
		ground = new Ground();
		ground->AddAnimation(303);
		ground->SetPosition(0 + i * 32, 480 - 30);
		objects.push_back(ground);
		grid->AddObject(ground);
	}

	for (int i = 0; i < 2; i++)  // tạo 2 cục gạch trên cửa
	{
		ground = new Ground();
		ground->AddAnimation(303);
		ground->SetPosition(3041 + i * 32, 130);
		objects.push_back(ground);
		grid->AddObject(ground);
	}

	for (int i = 0; i < 2; i++) // tạo 2 cột gạch dưới cửa
	{
		for (int j = 0; j < 5; j++)
		{
			ground = new Ground();
			ground->AddAnimation(303);
			ground->SetPosition(3041 + i * 32, 290 + j * 32);
			objects.push_back(ground);
			grid->AddObject(ground);
		}
	}

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 5; j++)
		{
			ground = new Ground();
			ground->AddAnimation(303);
			ground->SetPosition(3584 + i * 32, 289 + j * 32);
			objects.push_back(ground);
			grid->AddObject(ground);
		}

	for (int i = 0; i < 5; i++)
	{
		ground = new Ground();
		ground->AddAnimation(303);
		ground->SetPosition(4064, 418 - 32 * i);
		objects.push_back(ground);
		grid->AddObject(ground);
	}

	for (int i = 0; i < 2; i++)
	{
		ground = new Ground();
		ground->AddAnimation(303);
		ground->SetPosition(3712 + 32 * i, 289);
		objects.push_back(ground);
		grid->AddObject(ground);
	}

	for (int i = 0; i < 2; i++)
	{
		ground = new Ground();
		ground->AddAnimation(303);
		ground->SetPosition(4032 + 32 * i, 130);
		objects.push_back(ground);
		grid->AddObject(ground);
	}

	for (int i = 0; i < 3; i++)
	{
		ground = new Ground();
		ground->AddAnimation(303);
		ground->SetPosition(5600, 130 + i * 32);
		objects.push_back(ground);
		grid->AddObject(ground);
	}

	for (int i = 0; i < 3; i++)
	{
		ground = new Ground();
		ground->AddAnimation(303);
		ground->SetPosition(5600, 353 + i * 32);
		objects.push_back(ground);
		grid->AddObject(ground);
	}


#pragma endregion


	


#pragma region Tạo cầu thang + gạch

	ground_null = new Ground0(); 
	ground_null->LoadResources();
	ground_null->AddAnimation(301);
	ground_null->setNx(-1);
	ground_null->SetState(1);
	ground_null->SetPosition(1233, 418);
	objects.push_back(ground_null);
	grid->AddObject(ground_null);
	for (int i = 0; i < 3; i++) // tạo nền gạch đầu tiên 
	{
		ground = new Ground();
		ground->AddAnimation(303);
		ground->SetPosition(1377 + i * 32, 321);
		objects.push_back(ground);
		grid->AddObject(ground);
	}
	stair->setCount(4);  // tạo cầu thang đầu tiên
	stair->AddAnimation(1502);
	stair->setNx(-1);
	stair->SetPosition(1249, 418);
	objects.push_back(stair);
	grid->AddObject(stair);

	ground_null = new Ground0();
	ground_null->AddAnimation(301);
	ground_null->setNx(1);
	ground_null->SetState(1);
	ground_null->SetPosition(1361, 232);
	objects.push_back(ground_null);
	grid->AddObject(ground_null);

	// tạo gạch + cầu thang thứ 2

	ground_null = new Ground0();
	ground_null->LoadResources();
	ground_null->AddAnimation(301);
	ground_null->setNx(-1);
	ground_null->SetState(1);
	ground_null->SetPosition(1425, 289);
	objects.push_back(ground_null);
	grid->AddObject(ground_null);
	for (int i = 0; i < 10; i++)
	{
		ground = new Ground();
		ground->AddAnimation(303);
		ground->SetPosition(1506 + i * 32, 257);
		objects.push_back(ground);
		grid->AddObject(ground);
	}
	stair = new Stair();
	stair->setCount(2);
	stair->AddAnimation(1502);
	stair->setNx(-1);
	stair->SetPosition(1441, 289);
	objects.push_back(stair);
	grid->AddObject(stair);

	ground_null = new Ground0();
	ground_null->LoadResources();
	ground_null->AddAnimation(301);
	ground_null->setNx(1);
	ground_null->SetState(1);
	ground_null->SetPosition(1489, 166);
	objects.push_back(ground_null);
	grid->AddObject(ground_null);

	// tạo gạch và cầu thang thứ 3

	ground_null = new Ground0();
	ground_null->LoadResources();
	ground_null->AddAnimation(301);
	ground_null->setNx(1);
	ground_null->SetState(-1);
	ground_null->SetPosition(1810, 168);
	objects.push_back(ground_null);
	grid->AddObject(ground_null);
	for (int i = 0; i < 6; i++)
	{
		ground = new Ground();
		ground->AddAnimation(303);
		ground->SetPosition(1858 + i * 32, 321);
		objects.push_back(ground);
		grid->AddObject(ground);
	}
	stair = new Stair();
	stair->setCount(2);
	stair->AddAnimation(1501);
	stair->setNx(1);
	stair->SetPosition(1826, 258);
	objects.push_back(stair);
	grid->AddObject(stair);

	ground_null = new Ground0();
	ground_null->LoadResources();
	ground_null->AddAnimation(301);
	ground_null->setNx(-1);
	ground_null->SetState(-1);
	ground_null->SetPosition(1874, 289);
	objects.push_back(ground_null);
	grid->AddObject(ground_null);


	// tạo gạch và cầu thang trước Door + gạch sau door

	ground_null = new Ground0();
	ground_null->LoadResources();
	ground_null->AddAnimation(301);
	ground_null->setNx(-1);
	ground_null->SetState(1);
	ground_null->SetPosition(2574, 418);
	objects.push_back(ground_null);
	grid->AddObject(ground_null);
	for (int i = 0; i < 17; i++)
	{
		ground = new Ground();
		ground->AddAnimation(303);
		ground->SetPosition(2782 + i * 32, 258);
		objects.push_back(ground);
		grid->AddObject(ground);
	}
	stair = new Stair();
	stair->setCount(6);
	stair->AddAnimation(1502);
	stair->setNx(-1);
	stair->SetPosition(2590, 418);
	objects.push_back(stair);
	grid->AddObject(stair);

	ground_null = new Ground0();
	ground_null->AddAnimation(301);
	ground_null->setNx(1);
	ground_null->SetState(1);
	ground_null->SetPosition(2766, 168);
	objects.push_back(ground_null);
	grid->AddObject(ground_null);
	
	// tạo gạch + cầu thang sau door 1
	ground_null = new Ground0();
	ground_null->LoadResources();
	ground_null->AddAnimation(301);
	ground_null->setNx(1);
	ground_null->SetState(-1);
	ground_null->SetPosition(3406, 232);
	objects.push_back(ground_null);
	grid->AddObject(ground_null);
	for (int i = 0; i < 3; i++)
	{
		ground = new Ground();
		ground->AddAnimation(303);
		ground->SetPosition(3326 + i * 32, 321);
		objects.push_back(ground);
		grid->AddObject(ground);
	}
	stair = new Stair();
	stair->setCount(4);
	stair->AddAnimation(1501);
	stair->setNx(1);
	stair->SetPosition(3422, 321);
	objects.push_back(stair);
	grid->AddObject(stair);

	ground_null = new Ground0();
	ground_null->LoadResources();
	ground_null->AddAnimation(301);
	ground_null->setNx(-1);
	ground_null->SetState(-1);
	ground_null->SetPosition(3534, 418);
	objects.push_back(ground_null);
	grid->AddObject(ground_null);



	// tạo cầu thang + nền gạch sau cầu thang xuống thứ nhất
	ground_null = new Ground0();
	ground_null->LoadResources();
	ground_null->AddAnimation(301);
	ground_null->setNx(1);
	ground_null->SetState(-1);
	ground_null->SetPosition(3145, 361);
	objects.push_back(ground_null);
	grid->AddObject(ground_null);

	stair = new Stair();
	stair->setCount(1);
	stair->AddAnimation(1501);
	stair->setNx(1);
	stair->SetPosition(3169, 480 - 30);
	objects.push_back(stair);
	grid->AddObject(stair);

	for (int i = 0; i < 19; i++)
	{
		ground = new Ground();
		ground->AddAnimation(303);
		ground->SetPosition(3201 + i * 32, 480 - 30);
		objects.push_back(ground);
		grid->AddObject(ground);
	}


	// tạo nhóm gạch ở dưới phần dưới
	for (int i = 0; i < 14; i++)
	{
		ground = new Ground();
		ground->AddAnimation(303);
		ground->SetPosition(3072 + i * 32, 801);
		objects.push_back(ground);
		grid->AddObject(ground);
	}

	ground_null = new Ground0();
	ground_null->LoadResources();
	ground_null->AddAnimation(301);
	ground_null->setNx(-1);
	ground_null->SetState(-1);
	ground_null->SetPosition(3248, 706);
	objects.push_back(ground_null);
	grid->AddObject(ground_null);
	for (int i = 0; i < 2; i++)
	{
		ground = new Ground();
		ground->AddAnimation(303);
		ground->SetPosition(3264 + i * 32, 738);
		objects.push_back(ground);
		grid->AddObject(ground);
	}
	for (int i = 0; i < 2; i++)
	{
		ground = new Ground();
		ground->AddAnimation(303);
		ground->SetPosition(3584 + i * 32, 801);
		objects.push_back(ground);
		grid->AddObject(ground);
	}

	for (int i = 0; i < 10; i++)
	{
		ground = new Ground();
		ground->AddAnimation(303);
		ground->SetPosition(3712 + i * 32, 801);
		objects.push_back(ground);
		grid->AddObject(ground);
	}
	ground_null = new Ground0();
	ground_null->LoadResources();
	ground_null->AddAnimation(301);
	ground_null->setNx(-1);
	ground_null->SetState(-1);
	ground_null->SetPosition(3952, 769);
	objects.push_back(ground_null);
	grid->AddObject(ground_null);

	for (int i = 0; i < 8; i++)
	{
		ground = new Ground();
		ground->AddAnimation(303);
		ground->SetPosition(4064, 640 + i * 32);
		objects.push_back(ground);
		grid->AddObject(ground);
	}

	ground = new Ground();
	ground->AddAnimation(303);
	ground->SetPosition(4032, 864);
	objects.push_back(ground);
	grid->AddObject(ground);


	// tạo gạch bên cầu thang xuống 2 + cầu thang xuống 2 + nền gạch sau cầu thang 2

	ground_null = new Ground0();
	ground_null->LoadResources();
	ground_null->AddAnimation(301);
	ground_null->setNx(1);
	ground_null->SetState(-1);
	ground_null->SetPosition(3786, 361);
	objects.push_back(ground_null);
	grid->AddObject(ground_null);

	stair = new Stair();
	stair->setCount(1);
	stair->AddAnimation(1501);
	stair->setNx(1);
	stair->SetPosition(3809, 480 - 30);
	objects.push_back(stair);
	grid->AddObject(stair);

	for (int i = 0; i < 56; i++)
	{
		ground = new Ground();
		ground->AddAnimation(303);
		ground->SetPosition(3840 + 32 * i, 480 - 30);
		objects.push_back(ground);
		grid->AddObject(ground);
	}

	// cầu thang lên trước door 2
	ground_null = new Ground0();
	ground_null->LoadResources();
	ground_null->AddAnimation(301);
	ground_null->setNx(1);
	ground_null->SetState(-1);
	ground_null->SetPosition(3852, 232);
	objects.push_back(ground_null);
	grid->AddObject(ground_null);

	for (int i = 0; i < 3; i++)
	{
		ground = new Ground();
		ground->AddAnimation(303);
		ground->SetPosition(3776 + 32 * i, 321);
		objects.push_back(ground);
		grid->AddObject(ground);
	}

	stair = new Stair();
	stair->setCount(4);
	stair->AddAnimation(1501);
	stair->setNx(1);
	stair->SetPosition(3872, 321);
	objects.push_back(stair);
	grid->AddObject(stair);

	ground_null = new Ground0();
	ground_null->LoadResources();
	ground_null->AddAnimation(301);
	ground_null->setNx(-1);
	ground_null->SetState(-1);
	ground_null->SetPosition(3984, 418);
	objects.push_back(ground_null);
	grid->AddObject(ground_null);


	for (int i = 0; i < 13; i++)
	{
		ground = new Ground();
		ground->AddAnimation(303);
		ground->SetPosition(3904 + 32 * i, 258);
		objects.push_back(ground);
		grid->AddObject(ground);
	}

	// tạo gạch + cầu thang sau cửa thứ 2

	ground_null = new Ground0();
	ground_null->LoadResources();
	ground_null->AddAnimation(301);
	ground_null->setNx(1);
	ground_null->SetState(-1);
	ground_null->SetPosition(4304, 167);
	objects.push_back(ground_null);
	grid->AddObject(ground_null);
	for (int i = 0; i < 11; i++)
	{
		ground = new Ground();
		ground->AddAnimation(303);
		ground->SetPosition(4352 + 32 * i, 321);
		objects.push_back(ground);
		grid->AddObject(ground);
	}
	stair = new Stair();
	stair->setCount(2);
	stair->AddAnimation(1501);
	stair->setNx(1);
	stair->SetPosition(4320, 258);
	objects.push_back(stair);
	grid->AddObject(stair);

	ground_null = new Ground0();
	ground_null->LoadResources();
	ground_null->AddAnimation(301);
	ground_null->setNx(-1);
	ground_null->SetState(-1);
	ground_null->SetPosition(4368, 289);
	objects.push_back(ground_null);
	grid->AddObject(ground_null);

	ground_null = new Ground0();
	ground_null->LoadResources();
	ground_null->AddAnimation(301);
	ground_null->setNx(1);
	ground_null->SetState(-1);
	ground_null->SetPosition(4688, 232);
	objects.push_back(ground_null);
	grid->AddObject(ground_null);

	stair = new Stair();
	stair->setCount(4);
	stair->AddAnimation(1501);
	stair->setNx(1);
	stair->SetPosition(4704, 321);
	objects.push_back(stair);
	grid->AddObject(stair);

	ground_null = new Ground0();
	ground_null->LoadResources();
	ground_null->AddAnimation(301);
	ground_null->setNx(-1);
	ground_null->SetState(-1);
	ground_null->SetPosition(4816, 418);
	objects.push_back(ground_null);
	grid->AddObject(ground_null);



	for (int i = 0; i < 2; i++)
	{
		ground = new Ground();
		ground->AddAnimation(303);
		ground->SetPosition(5440 + 32 * i, 385);
		objects.push_back(ground);
		grid->AddObject(ground);
	}
	
	ground_null = new Ground0();
	ground_null->LoadResources();
	ground_null->AddAnimation(301);
	ground_null->setNx(-1);
	ground_null->SetState(1);
	ground_null->SetPosition(5456, 353);
	objects.push_back(ground_null);
	grid->AddObject(ground_null);

	
	stair = new Stair();
	stair->setCount(2);  // tạo cầu thang đầu tiên
	stair->AddAnimation(1502);
	stair->setNx(-1);
	stair->SetPosition(5472, 353);
	objects.push_back(stair);
	grid->AddObject(stair);


	for (int i = 0; i < 3; i++)
	{
		ground = new Ground();
		ground->AddAnimation(303);
		ground->SetPosition(5536 + 32 * i, 321);
		objects.push_back(ground);
		grid->AddObject(ground);
	}

	ground_null = new Ground0();
	ground_null->AddAnimation(301);
	ground_null->setNx(1);
	ground_null->SetState(1);
	ground_null->SetPosition(5520, 232);
	objects.push_back(ground_null);
	grid->AddObject(ground_null);

#pragma endregion

	


	
	item = new Items();
	item->LoadResources();
	
	
#pragma region Load nến
	mcandle = new mCandle();
	mcandle->LoadResources();



	for (int i = 0; i < 5; i++)
	{
		mcandle = new mCandle();
		mcandle->isDropItem = true;
		mcandle->AddAnimation(402);
		mcandle->SetPosition(100 + i * 250, 480 - 96);
		objects.push_back(mcandle);
		grid->AddObject(mcandle);
	}

	for (int i = 0; i < 5; i++)
	{
		mcandle = new mCandle();
		mcandle->isDropItem = true;
		mcandle->AddAnimation(402);
		mcandle->SetPosition(200 + i * 250, 480 - 160);
		objects.push_back(mcandle);
		grid->AddObject(mcandle);
	}
	for (int i = 0; i < 2; i++)
	{
		mcandle = new mCandle();
		mcandle->isDropItem = true;
		mcandle->AddAnimation(402);
		mcandle->SetPosition(1320 + i * 600, 175);
		objects.push_back(mcandle);
		grid->AddObject(mcandle);
	}

	mcandle = new mCandle();
	mcandle->isDropItem = true;
	mcandle->AddAnimation(402);
	mcandle->SetPosition(1450, 480 - 96);
	objects.push_back(mcandle);
	grid->AddObject(mcandle);

	mcandle = new mCandle();
	mcandle->isDropItem = true;
	mcandle->AddAnimation(402);
	mcandle->SetPosition(1650, 165);
	objects.push_back(mcandle);
	grid->AddObject(mcandle);

	mcandle = new mCandle();
	mcandle->isDropItem = true;
	mcandle->AddAnimation(402);
	mcandle->SetPosition(1750, 195);
	objects.push_back(mcandle);
	grid->AddObject(mcandle);

	for (int i = 0; i < 5; i++)
	{
		mcandle = new mCandle();
		mcandle->isDropItem = true;
		mcandle->AddAnimation(402);
		mcandle->SetPosition(1950 + i * 300, 480 - 96);
		objects.push_back(mcandle);
		grid->AddObject(mcandle);
	}
	for (int i = 0; i < 2; i++)
	{
		mcandle = new mCandle();
		mcandle->isDropItem = true;
		mcandle->AddAnimation(402);
		mcandle->SetPosition(2850 + i * 400, 195);
		objects.push_back(mcandle);
		grid->AddObject(mcandle);
	}
	for (int i = 0; i < 2; i++)
	{
		mcandle = new mCandle();
		mcandle->isDropItem = true;
		mcandle->AddAnimation(402);
		mcandle->SetPosition(2950 + i * 400, 165);
		objects.push_back(mcandle);
		grid->AddObject(mcandle);
	}
	mcandle = new mCandle();
	mcandle->isDropItem = true;
	mcandle->AddAnimation(402);
	mcandle->SetPosition(3500, 321);
	objects.push_back(mcandle);
	grid->AddObject(mcandle);

	mcandle = new mCandle();
	mcandle->isDropItem = true;
	mcandle->AddAnimation(402);
	mcandle->SetPosition(3700, 165);
	objects.push_back(mcandle);
	grid->AddObject(mcandle);

	for (int i = 0; i < 6; i++)
	{
		mcandle = new mCandle();
		mcandle->isDropItem = true;
		mcandle->AddAnimation(402);
		mcandle->SetPosition(3300 + i * 200, 650);
		objects.push_back(mcandle);
		grid->AddObject(mcandle);
	}

	mcandle = new mCandle();
	mcandle->isDropItem = true;
	mcandle->AddAnimation(402);
	mcandle->SetPosition(3900, 195);
	objects.push_back(mcandle);
	grid->AddObject(mcandle);

	mcandle = new mCandle();
	mcandle->isDropItem = true;
	mcandle->AddAnimation(402);
	mcandle->SetPosition(4000, 165);
	objects.push_back(mcandle);
	grid->AddObject(mcandle);

	mcandle = new mCandle();
	mcandle->isDropItem = true;
	mcandle->AddAnimation(402);
	mcandle->SetPosition(4260, 195);
	objects.push_back(mcandle);
	grid->AddObject(mcandle);

	mcandle = new mCandle();
	mcandle->isDropItem = true;
	mcandle->AddAnimation(402);
	mcandle->SetPosition(4360, 165);
	objects.push_back(mcandle);
	grid->AddObject(mcandle);

	for (int i = 0; i < 5; i++)
	{
		mcandle = new mCandle();
		mcandle->isDropItem = true;
		mcandle->AddAnimation(402);
		mcandle->SetPosition(4400 + i * 200, 480 - 96);
		objects.push_back(mcandle);
		grid->AddObject(mcandle);
	}
#pragma endregion

	
}






void GameState2::Update(DWORD gameTime)
{
	if (simon->checkDie())
	{
		boss->SimonDie();
		isColisionDoor2 = true;
		//simon->Respawn(simon->getCheckPoint());
		
	}

	grid->isStopWatch = simon->checkStopWatch();
	boss->Run(simon->x);
	for (int i = 0; i < 3; i++)
	{
		panther[i]->Run(simon->x);
		if (panther[i]->isEnable == false )
		{
			panther[i]->Reload(simon->x);
			if (panther[i]->reload == true)
			{
				grid->AddObject(panther[i]);
				panther[i]->reload = false;
			}
		}
		if ((panther[i]->x > simon->x + 600 && panther[i]->checkRun() == true && panther[i]->nx > 0) || (panther[i]->checkRun() == true && panther[i]->x < simon->x - 600 && panther[i]->nx < 0))
		{
			panther[i]->Reload(simon->x);
			if (panther[i]->reload == true)
			{
				panther[i]->reload = false;
			}

		}
	}
	for (int i = 0; i < 4; i++)
	{
		merman[i]->Run(simon->x);
		merman[i]->isMapWater = tileMap->isCheck;
		/*if (merman[i]->isEnable == false)
		merman[i]->Reload(simon->x);*/
	}


	
	for (int i = 0; i < 9; i++)
	{
		zombies[i]->Run(simon->x);
		if (zombies[i]->isEnable == false || (zombies[i]->x > simon->x + 500 && zombies[i]->checkRun() == true && zombies[i]->getPrex() + 200) || (zombies[i]->x < simon->x - 500 && zombies[i]->checkRun() == true && zombies[i]->getPrex() - 200))
		{
			zombies[i]->Reload(simon->x);
			if (zombies[i]->reload == true)
			{
				grid->AddObject(zombies[i]);
				zombies[i]->reload = false;
			}
		}
	}

	bats[0]->Run(simon->x);
	//bats[0]->Reload(simon->x);
	bats[1]->Run(simon->x);
	//bats[1]->Reload(simon->x);
	
	
	if (boss->isEnable)
	{
		boss->AimSimon(objects[0], gameTime);
	}
	time = 300 - Countdown / 100.;
	ui->Update(boss->GetHP(), time, 3, 1);
	Countdown++;
	if (simon->checkColisionDoor() == true)
	{

		if (game->getCamX() + SCREEN_WIDTH / 2 < door->x)
		{
			pos.x = game->getCamX();
			pos.x += SIMON_WALKING_SPEED * gameTime;
			game->setCamPosition(pos.x, 0);
			count = 0;
		}
		else
		{

			if (count < 50)
			{
				if (count < 25)
					door->SetState(1);
				else
					door->SetState(2);
			}
			else
			{
				if (simon->x < door->x + 110)
				{
					simon->SetSpeed(0.001f, 0);
					simon->setNx(1);
					simon->SetState(SIMON_STATE_WALK);
					count = 50;
				}
				else
				{
					simon->SetSpeed(0, 0);
					if (count > 50 && count < 100)
					{
						if (count < 75)
						{
							door->SetState(2);
						}
						else if( count < 90)
						{
							door->SetState(1);
						}
						else 
						{
							door->SetState(0);
						}
					}
					else if (pos.x < door->x + 20)
					{
						pos.x = game->getCamX();
						pos.x += SIMON_WALKING_SPEED * gameTime;
						game->setCamPosition(pos.x, 0);
					}
					else {
						simon->setColisionDoor(false);
						D3DXVECTOR2 temp;
						simon->GetPosition(temp.x, temp.y);
						simon->setCheckPoint(temp);

						door->SetPosition(4072, 162);
						if (simon->x > 4150)
						{
							isColisionDoor2 = true;
						}
						return;
					}
				}
			}
		}

		count++;
		objects[0]->Update(gameTime);
		return;
	}


	Control();
	if ( simon->y >= 405 && !isCheck)
	{
		//simon->SetState(SIMON_STATE_CHANGE);
		if (simon->y >= 415)
		{
			tileMap->isCheck = true;
			isColisionDoor = true;
			isCheck = true;
			isCheck1 = false;

			simon->SetPosition(simon->x + 15, 606);
			if (simon->x < 3500)
				pos.x = simon->x - 100;
			else
				pos.x = simon->x - 367;
			pos.y = 480;
			game->setCamPosition(pos.x, pos.y);
		}
	}
	else if ( simon->y <= 605 && simon->y >= 590 && !isCheck1)
	{
		isCheck = false;
		isCheck1 = true;
		tileMap->isCheck = false;

		simon->SetPosition(simon->x - 15, 407);
		if(simon->x > 3500)
			pos.x = simon->x -367;
		else
			pos.x = simon->x - 115;
		pos.y = 0;
		game->setCamPosition(pos.x, pos.y);
	}
	else if (simon->y >= 876 && !isCheck1 && tileMap->isCheck == true)
	{
		
		if (isStart == false)
		{
			isStart = true;
			timeStart += GetTickCount();

			EffectDead * effect = new EffectDead();
			effect->LoadResources();
			effect->SetPosition(simon->x, simon->y);
			effect->state = 2;
			effect->isEffect = false;
			objects.push_back(effect);
			grid->AddObject(effect);
			simon->setLife(1);
		}
		else
		{
			if (GetTickCount() - timeStart > 1000)
			{
				timeStart = 0;
				isStart = false;
				if(simon->x < 3073)
					isColisionDoor = false;
				else 
					isColisionDoor = true;
				isCheck = false;;
				isCheck1 = true;
				tileMap->isCheck = false;
				simon->Respawn(simon->getCheckPoint());
				pos.x = simon->getCheckPoint().x - 115;
				pos.y = 0;
				game->setCamPosition(pos.x, pos.y);
			}
		}
	}
	grid->DeleteEnable();
	grid->Update(simon->x, simon->y, SCREEN_HEIGHT, SCREEN_WIDTH,gameTime);

	if (simon->x < SCREEN_WIDTH / 2)
	{
		pos.x = 0;
		game->setCamPosition(pos.x, 0);
	}

	if (simon->x >= SCREEN_WIDTH / 2 && simon->x <= 3073 - SCREEN_WIDTH / 2 && isColisionDoor == false)
	{
		simon->getX(pos.x);
		pos.x -= SCREEN_WIDTH / 2;
		game->setCamPosition(pos.x, 0);

	}
	else if (simon->x >= 3073 + SCREEN_WIDTH / 2 && simon->x <= 4090  - SCREEN_WIDTH / 2 && isColisionDoor == true)
	{
		simon->getX(pos.x);
		pos.x -= SCREEN_WIDTH / 2;
		game->setCamPosition(pos.x, pos.y);
	}
	else if (simon->x >= 4101 + SCREEN_WIDTH / 2 && simon->x <= 5628 - SCREEN_WIDTH / 2 && isColisionDoor2 == true)
	{
		simon->getX(pos.x);
		pos.x -= SCREEN_WIDTH / 2;
		game->setCamPosition(pos.x, pos.y);
		if (simon->x >= 5307)
		{
			isColisionDoor2 = false;
		}
	}


}

void GameState2::Render()
{

	tileMap->DrawMap(pos);
	ui->Render();
	if (simon->checkColisionDoor() == true)
	{
		objects[1]->Render();
		objects[0]->Render();
		return;
	}
	grid->Draw(simon->x,simon->y, SCREEN_HEIGHT, SCREEN_WIDTH);
}

bool GameState2::GetChangingState()
{
	return GameState::GetChangingState();
}

void GameState2::SetChangingState(bool status)
{
	GameState::SetChangingState(status);
}

void GameState2::DestroyAll()
{
	//delete(simon);
	SAFE_DELETE(tileMap);
	SAFE_DELETE(ground);

	objects.clear();
	listItem.clear();
}

void GameState2::Control()
{
	if (simon->GetState() == SIMON_STATE_DIE || simon->checkFight() == true || simon->checkEffect() == true || simon->checkHurt() == true)
		return;

	if (IsKeyPress(DIK_Q))
	{
		isCheck = false;
		isCheck1 = true;
		tileMap->isCheck = false;
		boss->SimonDie();
		isColisionDoor2 = true;
		pos.x = simon->getCheckPoint().x - 115;
		pos.y = 0;
		game->setCamPosition(pos.x, pos.y);
		simon->Respawn(simon->getCheckPoint());
	}
	if (IsKeyPress(DIK_W))
	{
		simon->SetHP(1);
	}
	if (IsKeyDown(DIK_UP))
	{
		if (IsKeyPress(DIK_Z))
		{
			if (simon->checkUseItem() == true)
				return;
			if (simon->checkWeapon() == false)
				return;
			if (simon->checkWeapon() == true)
				simon->SetState(SIMON_STATE_USE_ITEM);

		}
	}
	else if (IsKeyPress(DIK_Z))
	{

		if (simon->checkFight() == false && (simon->checkJump() == true || simon->GetState() == SIMON_STATE_IDLE || simon->checkStair() == true))
			simon->SetState(SIMON_STATE_ATK);
		if (simon->checkFight() == false && simon->checkSit() == true && simon->checkStair() != true)
			simon->SetState(SIMON_STATE_S_ATK);
	}
	else if (IsKeyPress(DIK_SPACE))
	{
		if (simon->checkStair() == true)
			return;
		if (simon->checkGround() == true && simon->checkSit() == false)
			simon->SetState(SIMON_STATE_JUMP);
	}
	/*else if (IsKeyPress(DIK_X))
	{

		if (simon->checkUseItem() == true)
			return;
		if (simon->checkWeapon() == false)
			return;
		if (simon->checkWeapon() == true)
			simon->SetState(SIMON_STATE_USE_ITEM);

	}*/
	else if (IsKeyDown(DIK_RIGHT) && simon->checkSit() == false)
	{
		if (simon->checkStair() == true || simon->checkJump() == true)
			return;
		simon->setNx(1);
		simon->SetState(SIMON_STATE_WALK);
	}
	else if (IsKeyDown(DIK_LEFT) && simon->checkSit() == false)
	{
		if (simon->checkStair() == true || simon->checkJump() == true)
			return;
		simon->setNx(-1);
		simon->SetState(SIMON_STATE_WALK);
	}
	else if (IsKeyDown(DIK_DOWN))
	{
		if (simon->checkJump() == true)
			return;
		simon->SetState(SIMON_STATE_SIT);
	}
	else
	{
		if (simon->checkJump() == true)
			return;
		simon->SetState(SIMON_STATE_IDLE);
	}
}