#include "Simon.h"


int Simon::score = 0;

Simon::Simon()
{

}


Simon::~Simon()
{

}

bool Simon::Initialize(LPDIRECT3DDEVICE9 _gDevice, const char* _file, float _x, float _y, int tag)
{
	if (!GameObject::Initialize(_gDevice, _file, _x, _y, tag))
		return false;
	isLeft = false;



	simonSpeed = SPEED;
	currentDirection = 0;

	canControlKeyboard = true;

	doorCollideDirection = 0;
	isGoingThrowDoor = false;

	deadTime = 0;

	this->CreateAnimation();

	isInvincible = false;
	invincibleTime = INVINCIBLE_TIME;


	whip = new Whip();
	if (!whip->Initialize(_gDevice, WHIP_SPRITE, 0, 0, TAG_WHIP))
		return false;

	//////////////////////////// INIT SUB WEAPON ///////////////////////////


	noSubWeapon = 1;


	typeOfSubWeapon = 0;
	energy = 0;
	typeOfWhip = 1;

	return true;
}

void Simon::Reload()
{

	isInvincible = false;
	invincibleTime = INVINCIBLE_TIME;

	isGravity = true;
	isGrounded = false;
	this->isLeft = false;



	SetSize(sprite->GetWidth(), sprite->GetHeight());
	SetPosition(sprite->GetPosition());
	SetRegion(0, width, 0, -height);
	canControlKeyboard = true;
}



void Simon::SetInvincible(int time)
{
	invincibleTime = time;
	isInvincible = true;
}

void Simon::CreateAnimation()
{
	anim = new Animation();
	anim->Initialize(sprite, 60.0f, 66.0f, 0.15f);

	// Khoi tao animation dung yen
	std::vector<D3DXVECTOR2> standAnimation;
	standAnimation.push_back(D3DXVECTOR2(0, 0));

	//Khoi tao animation luc roi
	std::vector<D3DXVECTOR2> fallAnimation;
	fallAnimation.push_back(D3DXVECTOR2(0, 0));

	// Khoi tao animation luc di chuyen
	std::vector<D3DXVECTOR2> moveAnimation;
	moveAnimation.push_back(D3DXVECTOR2(0, 0));
	moveAnimation.push_back(D3DXVECTOR2(1, 0));
	moveAnimation.push_back(D3DXVECTOR2(2, 0));
	moveAnimation.push_back(D3DXVECTOR2(3, 0));

	//// Khoi tao animation luc ngoi
	std::vector<D3DXVECTOR2> sitAnimation;
	sitAnimation.push_back(D3DXVECTOR2(4, 0));

	//// Khoi tao animation luc nhay
	std::vector<D3DXVECTOR2> jumpAnimation;
	jumpAnimation.push_back(D3DXVECTOR2(4, 0));

	////Khoi tao animation luc danh roi khi dung
	std::vector<D3DXVECTOR2> hitStandAnimation;
	hitStandAnimation.push_back(D3DXVECTOR2(5, 0));
	hitStandAnimation.push_back(D3DXVECTOR2(6, 0));
	hitStandAnimation.push_back(D3DXVECTOR2(7, 0));

	std::vector<D3DXVECTOR2> throwSubWeapon;
	throwSubWeapon.push_back(D3DXVECTOR2(5, 0));
	throwSubWeapon.push_back(D3DXVECTOR2(6, 0));
	throwSubWeapon.push_back(D3DXVECTOR2(7, 0));

	////Khoi tao animation luc danh roi khi ngoi
	std::vector<D3DXVECTOR2> hitSitAnimation;
	hitSitAnimation.push_back(D3DXVECTOR2(7, 1));
	hitSitAnimation.push_back(D3DXVECTOR2(0, 2));
	hitSitAnimation.push_back(D3DXVECTOR2(1, 2));




	// Khoi tao animation nhay lui
	std::vector<D3DXVECTOR2> hurtedAnimation;
	hurtedAnimation.push_back(D3DXVECTOR2(0, 1));



	// Them cac animation
	anim->AddAnimation(STAND, standAnimation);
	anim->AddAnimation(MOVE, moveAnimation);
	anim->AddAnimation(SIT, sitAnimation);
	anim->AddAnimation(JUMP, jumpAnimation);
	anim->AddAnimation(HIT_STAND, hitStandAnimation);
	anim->AddAnimation(HIT_SIT, hitSitAnimation);
	anim->AddAnimation(FALL_DOWN, fallAnimation);

	anim->AddAnimation(HURTED, hurtedAnimation);

	anim->AddAnimation(THROW_SUB_WEAPON, throwSubWeapon);


	action = STAND;
}

void Simon::Update(float gameTime)
{
	SetRegion(0, width, 0, -height);

	if (velocity.y > 0)
		currentDirection = 1;
	else if (velocity < 0)
		currentDirection = -1;

	GravityHandle(gameTime);

	if (action != SIT && action != HIT_SIT && action != JUMP)
		Setbox(30, 0, -15, 0);
	else
		Setbox(30, 16, -15, 16);

	if (!isDead)
	{

			sprite->SetPosition(sprite->GetPosition().x + velocity.x * gameTime,
				sprite->GetPosition().y + velocity.y  * gameTime);

			anim->DoAnimation(action);
			anim->Update(gameTime);

			SetPosition(sprite->GetPosition());
			SetRegion(0, width, 0, -height);

	}
	else
	{
		if (isGrounded)
		{
			isInvincible = false;
			canControlKeyboard = false;
			action = DEAD;
		}
		else
		{
			sprite->SetPosition(sprite->GetPosition().x + velocity.x * gameTime,
				sprite->GetPosition().y + velocity.y  * gameTime);

		}
		anim->DoAnimation(action);
		anim->Update(gameTime);
	}

	whip->Update(gameTime);

	if (action == HIT_SIT || action == HIT_STAND )
		isFighting = !anim->CheckDoAllFrame();


	SetRegion(0, anim->frameWidth, 0, -anim->frameHeight);

	if (isInvincible)
		isSplashing = isSplashing ? false : true;
	else
		isSplashing = false;
}

void Simon::Render(Camera *cam)
{
	if (!isSplashing)
	{
		if (isFighting && (action == HIT_SIT || action == HIT_STAND))
		{
			whip->Render(cam);
		}
		anim->Render(sprite, isLeft, cam);
	}
}

D3DXVECTOR3 Simon::GetVelocity()
{
	return velocity;
}

void Simon::GravityHandle(float gameTime)
{
	velocity.y += EARTH_ACCELERATION * gameTime;
}

void Simon::Move()
{
	action = MOVE;
	velocity.x = ((isLeft) ? -1 : 1) * simonSpeed;
}

void Simon::Jump()
{
	velocity.y = JUMP_FORCE;
}

void Simon::Sit()
{
	velocity.x = 0;
	velocity.y = 0;
}

void Simon::Stand()
{
	//if (action != HURTED)
	if (action != STAND)
		velocity.x = 0;
	action = STAND;
	velocity.y = 0;
	whip->SetType(NORMAL_WHIP);
}

void Simon::Fight()
{
	isFighting = true;
	whip->SetType(typeOfWhip);
	Fighting();
}

void Simon::Fighting()
{
	if (!isFighting)
	{
		if (action == HIT_SIT)
		{
			action = SIT;
			Sit();
		}
		else
		{
				action = STAND;
				Stand();
		}
		whip->SetType(NORMAL_WHIP);
	}
	else
	{
		if (action == HIT_SIT)
			whip->SetPosition(D3DXVECTOR3(this->GetPosition().x, this->GetPosition().y, 0), false);
		else
			whip->SetPosition(D3DXVECTOR3(this->GetPosition().x, this->GetPosition().y, 0), true);
		whip->SetIsLeft(isLeft);
		if (isGrounded)
			velocity.x = 0;
	}
}



void Simon::UpdateKeyboard(float gameTime)
{
	if (canControlKeyboard)
	{
		if ((action != HURTED || isGrounded == true) && !(action == HIT_STAND && isGrounded == false))
		{
			if (IsKeyPress(DIK_SPACE) && isGrounded)
			{
				if (action == SIT || action == JUMP)
					return;
				action = JUMP;
				Jump();
				isGrounded = false;
			}

			if (isGrounded && velocity.y > 0 && action != JUMP && action != HURTED)
			{
				Stand();
			}
			else if (isGrounded && velocity.y == 0)
			
				Stand();
			}

			if (IsKeyDown(DIK_DOWN) )
			{
				if (action == JUMP || action == HURTED)
					return;
				action = SIT;
				Sit();
			}

			if (IsKeyDown(DIK_LCONTROL))
			{
				if (action == SIT)
					action = HIT_SIT;
				else
					action = HIT_STAND;
				Fight();
				return;
			}


			if (isGrounded == true)
			{
				velocity.x = 0;
			}

			if (IsKeyDown(DIK_LEFT))
			{
				if (action == JUMP && isGrounded == false)
					return;
				isLeft = true;
				if (action != SIT)
				{
					action = MOVE;
					Move();
				}
			}

			if (IsKeyDown(DIK_RIGHT))
			{
				if (action == JUMP && isGrounded == false)
					return;
				isLeft = false;
				if (action != SIT)
				{
					action = MOVE;
					Move();
				}
			}
	}
}

void Simon::KeyBoardHandle(float gameTime)
{
	if (action == HIT_SIT || action == HIT_STAND)
		Fighting();
	else
		UpdateKeyboard(gameTime);
}



void Simon::CheckCollider(float gameTime, std::vector<GameObject*> *listGameObject)
{


	CheckCollideWithGround(gameTime, listGameObject);
	//CheckColliderWithMovableGround(gameTime, listGameObject);
	
	WhipCheckCollider(gameTime, listGameObject);
}



void Simon::CheckCollideWithGround(float gameTime, std::vector<GameObject*>* listGameObject)
{
	float normalX = 0;
	float normalY = 0;

	for (std::vector<GameObject*>::iterator i = listGameObject->begin(); i != listGameObject->end(); i++)
	{
		if ((*i)->GetCollider()->GetTag() == TAG_GROUND )
		{
			Box tempBox = (*i)->GetCollider()->GetBox();
			if (collider->AABBCheck(collider->GetBox(), (*i)->GetCollider()->GetBox()))
			{
				isGrounded = false;
			}
			Box broadphaseBox = collider->GetSweptBoardphaseBox(collider->GetBox(), gameTime);
			if (collider->AABBCheck(broadphaseBox, (*i)->GetCollider()->GetBox()))
			{
				Box tempBox = (*i)->GetCollider()->GetBox();
				timeCollideGround = collider->SweptAABB(gameTime, collider->GetBox(), (*i)->GetCollider()->GetBox(), normalX, normalY);
				if ((timeCollideGround >= 0.0f && timeCollideGround < 1.0f))
				{
					if (normalY == 1)
					{
						isGrounded = true;
						if (isGrounded)	
						{
							if (action != SIT && action != HIT_SIT && action != JUMP)
								sprite->SetPosition(sprite->GetPosition().x,
									collider->GetBox().top + gameTime * timeCollideGround * velocity.y + 0.1);
							else
								sprite->SetPosition(sprite->GetPosition().x,
									collider->GetBox().top + gameTime * timeCollideGround * velocity.y + 0.1 + 16);
							velocity.y = 0;
						}

						return;
					}
				}
			}
			else
				isGrounded = false;
		}
	}
}

void Simon::CheckCollideWithGround(float gameTime, GameObject *gameObject)
{
	float normalX = 0;
	float normalY = 0;
	float timeCollide;
	Box tempBox = gameObject->GetCollider()->GetBox();
	if (collider->AABBCheck(collider->GetBox(), gameObject->GetCollider()->GetBox()))
	{
		isGrounded = false;
	}
	Box broadphaseBox = collider->GetSweptBoardphaseBox(collider->GetBox(), gameTime);
	if (collider->AABBCheck(broadphaseBox, gameObject->GetCollider()->GetBox()))
	{
		Box tempBox = gameObject->GetCollider()->GetBox();
		timeCollide = collider->SweptAABB(gameTime, collider->GetBox(), gameObject->GetCollider()->GetBox(), normalX, normalY);
		if ((timeCollide >= 0.0f && timeCollide < 1.0f))
		{
			if (normalY == 1)
			{
				sprite->SetPosition(sprite->GetPosition().x,
					collider->GetBox().top + gameTime * timeCollide * velocity.y + 0.1);
				velocity.y = 0;
				isGrounded = true;
				return;
			}
		}
	}
	else
		isGrounded = false;
}


void Simon::CheckColliderWith(float gameTime, GameObject *object)
{
	float normalX = 0;
	float normalY = 0;
	float timeCollide;

	if (object->GetTag() == TAG_GROUND)
	{
		Box broadphaseBox = collider->GetSweptBoardphaseBox(collider->GetBox(), gameTime);
		if (collider->AABBCheck(broadphaseBox, object->GetCollider()->GetBox()))
		{
			Box tempBox = object->GetCollider()->GetBox();
			timeCollide = collider->SweptAABB(gameTime, collider->GetBox(), object->GetCollider()->GetBox(), normalX, normalY);
		}
	}
}


void Simon::WhipCheckCollider(float gameTime, std::vector<GameObject*>* listGameObject)
{
	if (isFighting && whip->GetCurrentFrameOfWhip() == 2)
	{
		if (typeOfWhip < 3)
			whip->SetBox(whip->GetPosition().x + (isLeft ? 50 : 145), whip->GetPosition().y - 22, 45, 5, 0, 0);
		else
			whip->SetBox(whip->GetPosition().x + (isLeft ? 20 : 140), whip->GetPosition().y - 22, 70, 5, 0, 0);
		whip->CheckCollider(gameTime, listGameObject);
	}
}

void Simon::Setbox(float offsetW, float offsetH, float offsetX, float offsetY)
{
	GameObject::SetBox(sprite->GetPosition().x - offsetX,
		sprite->GetPosition().y - offsetY,
		anim->frameWidth - offsetW,
		anim->frameHeight - offsetH,
		velocity.x,
		velocity.y);
}