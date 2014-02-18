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
	bool m_jump;
	bool m_doubleJump;
	bool m_readyToFly;
	bool m_isFlying;

	//Size m_visibleSize;
	//Point m_origin;

	int m_sawyerRunFrame;

	Animation* m_pStandFrames;
	Animation* m_pRunFrames;
	Animation* m_pJumpFrames;
	Animation* m_pHitFrames;
	Animation* m_pFlightFrames;
	Animation* m_pLandingFrames;

	Action* m_pStandAction;
	Action* m_pRunAction;
	Action* m_pJumpAction;
	Action* m_pHitAction;
	Action* m_pFlightAction;
	Action* m_pLandingAction;

	InputAction* m_pForward;
	InputAction* m_pBackward;
	InputAction* m_pJump;

	Vector<SpriteFrame*> frames;
	String* filename;
	SpriteFrame* frame;

	SpriteFrameCache* m_pSpriteFrame;
	SpriteBatchNode* m_pSpriteBatch;
};

#endif // !__PLAYER_H__
