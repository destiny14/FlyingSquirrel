#ifndef __SLIMEHEAP_H__
#define __SLIMEHEAP_H__

#define TAG_SLIMEHEAP 123456

#include "cocos2d.h"
#include "Moveable.h"
#include <vector>
#include "Shooter.h"
#include "Player.h"
#include "MainLayer.h"
#include "Ground.h"

class SlimeHeap : public Shooter
{
protected:

	SlimeHeap(PhysicsEngine* _pEn);
	virtual ~SlimeHeap();
	bool init();
	void CheckForCollisions();
	bool canAttack();
	void moodWalk(float dt);
	void moodAttack(float dt);
	void moodDie(float dt);

public:

	void killIt();
	int attackRange = 160;
	void update(float dt);
	static SlimeHeap* create(PhysicsEngine* _pEn, MainLayer* layer);
	virtual bool onCollision(PhysicsObject* _other, int myColliderTag);
	float getTimer();
	void setTimer(float seconds);

private:

	MainLayer* m_layer;
	bool m_isAlive = true;
	bool m_isDead = false;
	float m_timer = 3.0;
	float m_tmpTimer;
	float m_speed = 100.0f;
	Point m_moveDirection;
	bool m_isForward = true;
	bool m_canAttack = true;
	float m_attackTimer = 1.0f;
	//PlayerCollider* m_pcollider;

	Action* m_pWalkAction;
	Action* m_pShootAction;
	Action* m_pHitAction;
	Action* m_pDeadAction;


	Animation* m_pWalkFrames;
	Animation* m_pShootFrames;
	Animation* m_pDeadFrames;


	Vector<SpriteFrame*> frames;
	String* m_pSpriteString;
	SpriteFrame* m_pFrame;

	SpriteFrameCache* m_pSpriteFrame;
	SpriteBatchNode* m_pSpriteBatch;

	Player* m_pPlayer = nullptr;

	Point playerPos;
	Point slimePos;

	//bool m_topCollision;
	//bool m_bottomColWhileTopCol;
	//Ground* m_topCollisionGround;
};

#endif // __SLIMEHEAP_H__