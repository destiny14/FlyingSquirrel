#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Ground.h"
#include "Moveable.h"
#include "MainLayer.h"
#include "Input.h"
#include "Shooter.h"
#include "Bullet.h"
#include "SimpleAudioEngine.h"

enum EMovement
{
	None = 0,
	Left = 1,
	Right = 2,
	Jump = 4
};

class Player : public Shooter
{
public:
	static Player* create(PhysicsEngine* _pEn, char* filename, MainLayer* parent, InputManager* pManager);

	Player(PhysicsEngine* _pEn);
	~Player();

	virtual bool init();
	virtual void update(float dt);

	int getHealth();
	int getNuts();
	void setNuts(int nuts);
	bool m_isDead;

	void hit();
	bool cs_flight;
	bool cs_run;

	virtual int getTag() override { return TAG_PLAYER; }
private:
	int m_health;
	int m_nuts;

	int m_counterDeath;
	int m_counterToShoot;
	int m_counterToFall;
	int m_counterToRescueFly;
	int m_countToShoot;

	Point m_direction;
	float m_speed;
	bool m_jump;
	bool m_doubleJump;
	bool m_readyToFly;
	bool m_isFlying;
	bool m_rescueFly;
	bool m_shooted;
	bool m_readyToFall;
	bool m_noNuts;
	bool m_flySound;
	bool m_topCollision;
	bool m_bottomColWhileTopCol;
	Ground* m_topCollisionGround;

	///////////
	// Input //
	///////////

	EMovement m_movement;

	InputAction* m_pForward;
	InputAction* m_pBackward;
	InputAction* m_pJump;
	InputAction* m_pShoot;

	///////////////////////
	// Animationhandling //
	///////////////////////

	int m_sawyerRunFrame;

	Animation* m_pStandFrames;
	Animation* m_pRunFrames;
	Animation* m_pJumpFrames;
	Animation* m_pHitFrames;
	Animation* m_pFlightFrames;
	Animation* m_pLandingFrames;
	Animation* m_pDeathFrames;
	Animation* m_pShootFrames;
	Animation* m_pFallStartFrames;
	Animation* m_pFallFrames;
	Animation* m_pFallToFlyFrames;
	Animation* m_pDontKnowDirectionFrames;
	Animation* m_pJumpShootFrames;
	Animation* m_pDoubleJumpFrames;

	Action* m_pStandAction;
	Action* m_pRunAction;
	Action* m_pJumpAction;
	Action* m_pHitAction;
	Action* m_pFlightAction;
	Action* m_pLandingAction;
	Action* m_pDeathAction;
	Action* m_pShootAction;
	Action* m_pFallStartAction;
	Action* m_pFallAction;
	Action* m_pFallToFlyAction;
	Action* m_pDontKnowDirectionAction;
	Action* m_pJumpShootAction;
	Action* m_pDoubleJumpAction;

	Vector<SpriteFrame*> frames;
	String* filename;
	SpriteFrame* frame;

	SpriteFrameCache* m_pSpriteFrame;
	SpriteBatchNode* m_pSpriteBatch;
};
#endif // !__PLAYER_H__
