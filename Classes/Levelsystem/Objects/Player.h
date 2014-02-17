#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Ground.h"
#include "Moveable.h"
#include "..\Components\PlayerCollider.h"
#include "Layers\MainLayer.h"
#include "Input.h"

enum EMovement
{
	None = 0,
	Left = 1,
	Right = 2,
	Jump = 4
};

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

	EMovement m_movement;
	Point m_direction;
	float m_speed;
	bool m_doubleJump;
	bool m_readyToFly;

	//Size m_visibleSize;
	//Point m_origin;

	int m_sawyerRunFrame;

	Sprite* m_pStandFrames;
	Sprite* m_pRunFrames;
	Sprite* m_pJumpFrames;
	Sprite* m_pHitFrames;

	InputAction* m_pForward;
	InputAction* m_pBackward;
	InputAction* m_pJump;

	SpriteFrameCache* m_pSpriteFrame;
	SpriteBatchNode* m_pSpriteBatch;
};

#endif // !__PLAYER_H__
