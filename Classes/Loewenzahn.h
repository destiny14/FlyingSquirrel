#ifndef __LOEWENZAHN_H__
#define __LOEWENZAHN_H__

#include "cocos2d.h"
#include "Moveable.h"
#include <vector>
#include "Shooter.h"
#include "Player.h"
#include "MainLayer.h"
#include "Ground.h"

class Loewenzahn : public Shooter
{
protected:

	Loewenzahn(PhysicsEngine* _pEn);
	virtual ~Loewenzahn();
	bool init();
	void setCollider(float width, float height);
	void CheckForCollisions();
	bool canAttack();
	void moodIdle(float dt);
	void moodAttack(float dt);
	void moodDie(float dt);

public:

	int attackRange = 1500;
	void update(float dt);
	bool m_isAlive = true;
	//PlayerCollider* getPlayerColliderComponent();
	static Loewenzahn* create(PhysicsEngine* _pEn, MainLayer* layer);

private:

	float m_timer = 3.0;
	float m_speed = 100.0f;
	Point m_moveDirection;
	bool m_isForward = true;
	//PlayerCollider* m_pcollider;

	Action* m_pIdleAction;
	Action* m_pShootAction;
	Action* m_pHitAction;
	Action* m_pDeadAction;


	Animation* m_pIdleFrames;
	Animation* m_pShootFrames;
	Animation* m_pHitFrames;
	Animation* m_pDeadFrames;

	Vector<SpriteFrame*> frames;
	String* m_pSpriteString;
	SpriteFrame* m_pFrame;

	SpriteFrameCache* m_pSpriteFrame;
	SpriteBatchNode* m_pSpriteBatch;

	Player* m_pPlayer;

	Point playerPos;
	Point loewenzahnPos;

	//bool m_topCollision;
	//bool m_bottomColWhileTopCol;
	//Ground* m_topCollisionGround;
};

#endif // __LOEWENZAHN_H__