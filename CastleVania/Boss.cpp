#include "Boss.h"


Boss::Boss(int hp, int damage, int point)
{
	std::srand(time(0));
	atSpot = true;
	aimable = false;
	waitTime = 0;
	hurtTime = HURT_TIME;
	isHurt = false;
	this->hp = hp;
	this->damage = damage;
	this->point = point;
	simonPos.x = -1;
}

void Boss::Fly(float gameTime)
{
	
	D3DXVECTOR3 pos;
	GetPosition(pos.x, pos.y);
	pos.x += direction.x * vx * gameTime;
	pos.y += direction.y * vy * gameTime;
	
	if (std::sqrt(std::pow(simonPos.x - pos.x, 2) + std::pow(simonPos.y - pos.y, 2)) >= distance)
	{
		aimable = false;	
		pos.x = simonPos.x; 
		pos.y = simonPos.y;
	}

	SetPosition(pos.x, pos.y); 

	state = BOSS_ANI_FLY; 
}


void Boss::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BOSS_BBOX_WIDTH;
	bottom = y + BOSS_BBOX_HEIGHT;
}

void Boss::LoadResources()
{
	Sprites * sprites = Sprites::GetInstance();
	Animations * animations = Animations::GetInstance();
	LPANIMATION ani;
	Textures * textures = Textures::GetInstance();

	textures->Add(ID_TEX_BOSS, L"Resource\\sprites\\Bosses\\VAMPIRE_BAT.png", D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 texBoss = textures->Get(ID_TEX_BOSS);


	sprites->Add(200001, 0, 0, 100, 46, texBoss);
	sprites->Add(200002, 100, 0, 200, 46, texBoss);
	sprites->Add(200003, 200, 0, 300, 46, texBoss);

	ani = new Animation(100);  // idle
	ani->Add(200001);
	animations->Add(2001, ani);

	ani = new Animation(100);	// fly right
	ani->Add(200003);
	animations->Add(2002, ani);

	ani = new Animation(100);	// fly right
	ani->Add(200003);
	ani->Add(200002);
	animations->Add(2003, ani);

	AddAnimation(2001);
	AddAnimation(2002);
	AddAnimation(2003);

	state = BOSS_ANI_SLEEP;
}

void Boss::Render()
{
	animations[state]->Render(x,y);
}

void Boss::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (hp > 0)
	{
		if (isRun)
		{


			GameObject::Update(dt, coObjects);

			if (isHurt == true)
			{
				if (start == false)
				{
					start = true;
					hurtTime += GetTickCount();
					state = BOSS_ANI_HURTED;
					hp -= 2;
				}
				else
				{
					if (GetTickCount() - hurtTime > 500)
					{
						start = false;
						hurtTime = 0;
						isHurt = false; 
						state = BOSS_ANI_FLY;
					}
				}
			}
			

			else 
			{
				if (aimable == true) {
					if (waitTime > 0)
						waitTime -= dt;
					else
						Fly(dt);
				}
				else {
					if (atSpot == false) 
						FlyToRandomSpot(dt);
					else 
						RandomSpot(); 
				}
			}

		}

	}
	else
	{
			isEnable = false;
	}
}



void Boss::FlyToRandomSpot(float gameTime)
{
	
	distance = std::sqrt(
		std::pow(random.x - x, 2) +
		std::pow(random.y - y, 2));

	
	direction.x = (random.x - x) / distance;
	direction.y = (random.y - y) / distance;

	
	D3DXVECTOR2 pos;
	GetPosition(pos.x, pos.y);
	pos.x += direction.x * vx * gameTime;
	pos.y += direction.y * vy * gameTime;;

	
	if (std::sqrt(std::pow(random.x - pos.x, 2) + std::pow(random.y - pos.y, 2)) >= distance)
	{
		vx = 0.2f;
		vy = 0.2f;
		chaseTime = CHASE_TIME;

		aimable = true;
		atSpot = true;
		pos.x = random.x;
		pos.y = random.y;
	}

	SetPosition(pos.x, pos.y); // So we setup (valid) new position

	state = BOSS_ANI_FLY; // Batman's flying so action = fly



}

void Boss::AimSimon(LPGAMEOBJECT simon, DWORD dt)
{
	if (simonPos.x < 0) {
		simonPos = { simon->x, simon->y }; // lấy vị trí simon
	}
	else if (chaseTime >= 0) {
		chaseTime -= dt;
		simonPos = { simon->x, simon->y };
	}

	if (aimable == true)
	{
		distance = std::sqrt(
			std::pow(simonPos.x - x, 2) + // lấy khoảng cách chéo tới simon
			std::pow(simonPos.y - y, 2));

		direction.x = (simonPos.x - x) / distance; // lấy khoảng cách của tới simon theo x ,y
		direction.y = (simonPos.y - y) / distance;
	}
}

void Boss::RandomSpot()
{

	random.x = std::rand() % (600) + preX; // random trong khu vực
	random.y = std::rand() % (300 ) + preY;

	
	atSpot = false;
	waitTime = WAIT_TIME;
	vx = 0.25f;
	vy = 0.2f;
}

void Boss::SetState(int state)
{
	switch (state)
	{
	case BOSS_STATE_HURT:
		isHurt = true;
		break;

	}

}
