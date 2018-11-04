#include "Whip.h"



Whip::Whip()
{
}


Whip::~Whip()
{
}

bool Whip::Initialize(LPDIRECT3DDEVICE9 gDevice, const char* file, float x, float y, int tag)
{
	if (!GameObject::Initialize(gDevice, file, x, y, tag))
		return false;

	anim = new Animation();
	anim->Initialize(sprite, 240.0f, 66.0f, 0.15f);

	std::vector<D3DXVECTOR2> normalWhip;
	normalWhip.push_back(D3DXVECTOR2(0, 0));

	////Khoi tao animation cho roi Vampire Killer
	std::vector<D3DXVECTOR2> vampireKiller;
	vampireKiller.push_back(D3DXVECTOR2(0, 0));
	vampireKiller.push_back(D3DXVECTOR2(1, 0));
	vampireKiller.push_back(D3DXVECTOR2(2, 0));

	//////Khoi tao animation cho roi Chain Whip
	std::vector<D3DXVECTOR2> chainWhip;
	chainWhip.push_back(D3DXVECTOR2(0, 1));
	chainWhip.push_back(D3DXVECTOR2(1, 1));
	chainWhip.push_back(D3DXVECTOR2(2, 1));

	//////Khoi tao animation cho roi Morning Star
	std::vector<D3DXVECTOR2> morningStar;
	morningStar.push_back(D3DXVECTOR2(1, 2));
	morningStar.push_back(D3DXVECTOR2(2, 3));
	morningStar.push_back(D3DXVECTOR2(0, 5));

	anim->AddAnimation(NORMAL_WHIP, normalWhip);
	anim->AddAnimation(VAMPIRE_KILLER, vampireKiller);
	anim->AddAnimation(CHAIN_WHIP, chainWhip);
	anim->AddAnimation(MORNING_STAR, morningStar);

	type = NORMAL_WHIP;
	check = false;
	return true;
}

void Whip::SetType(int _type)
{
	type = _type;
	check = false;
}

void Whip::SetPosition(D3DXVECTOR3 _position, bool isStanding)
{
	_position.x -= 90.0f;
	if (!isStanding)
		_position.y -= 16.5f;
	sprite->SetPosition(_position.x, _position.y);
}

void Whip::SetIsLeft(bool _isLeft)
{
	isLeft = _isLeft;
}

void Whip::Render(Camera *cam)
{
	anim->Render(sprite, isLeft, cam);
}

void Whip::Update(float gameTime)
{
	anim->DoAnimation(type);
	anim->Update(gameTime);
}

void Whip::CheckCollider(float gameTime, std::vector<GameObject*> *listGameObject)
{
	float normalX = 0;
	float normalY = 0;
	float timeCollide;

	if (!check)
	{
		for (std::vector<GameObject*>::iterator i = listGameObject->begin(); i != listGameObject->end(); i++)
		{
			Box tempBox = (*i)->GetCollider()->GetBox();
			if (collider->AABBCheck(collider->GetBox(), (*i)->GetCollider()->GetBox()))
			{
					if ((*i)->GetTag() > 0
						&& (*i)->GetTag() != TAG_GROUND
						&& (*i)->GetTag() != 25
						&& (*i)->GetTag() != -25
						&& (*i)->GetTag() != 22
						&& (*i)->GetTag() != -22)
					{
						(*i)->SetDead(true);
						(*i)->GetCollideEffect()->SetVisible(true);

						check = true;
					}
					else if ((*i)->GetTag() == -3)
					{
						(*i)->SetEnable(false);
						check = true;
					}
			}

		}
	}
}

void Whip::CheckColliderWith(float gameTime, GameObject *object)
{
	if (object->IsEnable() == true)
	{
		float normalX = 0;
		float normalY = 0;
		float timeCollide;

		Box tempBox = (object)->GetCollider()->GetBox();

	}
}

