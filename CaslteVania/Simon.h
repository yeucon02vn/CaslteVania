#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Input.h"
#include "Collider.h"
#include "Global.h"
#include "Whip.h"

#define INVINCIBLE_TIME 2

class Simon : public GameObject
{
private:
	int noSubWeapon;
	Animation *anim;
	int action;
	bool isLeft;
	D3DXVECTOR3 velocity;
	int currentAnimID;

	float simonSpeed;

	Whip *whip;


	bool isFighting;
	bool isThrowing;




	bool isInvincible;
	float invincibleTime;
	int directionX = 0, directionY = 0;

	int typeOfSubWeapon;
	int typeOfWhip;
	int energy;

	bool isGravity;
	bool isGrounded;

	bool isSplashing;

	bool canControlKeyboard;


	/*bien nay dung de xac dinh vua roi simon di len hay xuong cau thang*/
	int currentDirection; // -1 0 1 , xuong - len

	D3DXVECTOR3 collideDoor;

	int doorCollideDirection;
	bool isGoingThrowDoor;
	D3DXVECTOR3 viewportCheckpoint;

	float timeCollideGround;

	float deadTime;
public:

	int currentWeapon;
	static int score;

	D3DXVECTOR3 simonCheckpoint;
	Simon();
	~Simon();
	bool Initialize(LPDIRECT3DDEVICE9 _gDevice, const char * _file, float _x, float _y, int tag);
	void Reload();
	void Render(Camera *cam);


	void CreateAnimation();
	void Update(float gameTime);
	void UpdateKeyboard(float gameTime);
	void Move();
	void Jump();
	void Sit();
	void Stand();
	void Fight();
	void Fighting();

	void KeyBoardHandle(float gameTime);
	void GravityHandle(float gameTime);

	D3DXVECTOR3 GetVelocity();
	void SetVelocity(D3DXVECTOR3 vel) { velocity = vel; }

	void CheckCollider(float gameTime, std::vector<GameObject*> *listGameObject);


	void CheckColliderWith(float gameTime, GameObject *object);
	void CheckCollideWithGround(float gameTime, std::vector<GameObject*>* listGameObject);
	void WhipCheckCollider(float gameTime, std::vector<GameObject*>* listGameObject);
	void CheckCollideWithGround(float gameTime, GameObject *gameObject);

	Whip* GetWhip() { return whip; }

	bool GetIsFighting() { return isFighting; }

	bool GetIsLeft() { return isLeft; }

	void SetIsLeft(bool status) { isLeft = status; }

	bool IsInvincible() { return isInvincible; }

	void Setbox(float offsetW, float offsetH, float offsetX, float offsetY);
	int GetAction() { return action; }

	void SetAction(int action) { this->action = action; }

	int GetNoSubWeapon() { return noSubWeapon; }


	void SetTypeOfWhip(int typeOfWhip) { this->typeOfWhip = typeOfWhip; }

	int GetTypeOfWhip() { return this->typeOfWhip; }

	void SetEnergy(int energy) { this->energy = energy; }

	int GetEnergy() { return this->energy; }

	void SetNoSubWeapon(int no) { noSubWeapon = no; }


	void SetInvincible(int time);


	D3DXVECTOR3 GetCollideDoor() { return collideDoor; }

	void SetCanControlKeyboard(bool status) { canControlKeyboard = status; }

	bool CanControllKeyboard() { return canControlKeyboard; }

	bool IsGoingThrowDoor() { return isGoingThrowDoor; }
};

