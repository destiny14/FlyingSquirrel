#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Ground.h"
#include "Moveable.h"
#include "..\Components\PlayerCollider.h"
#include "Layers\MainLayer.h"
#include "Input.h"

class Player : public Moveable
{
public:
	static Player* create(char* filename, MainLayer* parent, InputManager* pManager);

	Player();
	~Player();

	virtual bool init();
	virtual void update(float dt);

	// setCollider()
	//
	// setzt die Kollider entsprechend der gesetzten Texur
	void setCollider();

	PlayerCollider* getPlayerColliderComponent();

private:
	void CheckForCollisions();

	Point m_direction;
	float m_speed;

	int m_sawyerRunFrame;

	InputAction* m_pForward;
	InputAction* m_pBackward;
	InputAction* m_pJump;
};

#endif // !__PLAYER_H__