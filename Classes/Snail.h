#ifndef __SNAIL_H__
#define __SNAIL_H__

#define TAG_SNAIL 46745

#include "cocos2d.h"
#include "Moveable.h"
#include <vector>
#include "Shooter.h"
#include "Player.h"
#include "MainLayer.h"
#include "PlayerCollider.h"
#include "Ground.h"

class Snail : public Shooter
{
protected:

	Snail();
	virtual ~Snail();
	bool init();
	void setCollider(float width, float height);
	void CheckForCollisions();
	bool canAttack();
	void moodWalk(float dt);
	void moodAttack(float dt);
	void moodDie(float dt);

public:

	void killIt();
	int attackRange = 180;
	void update(float dt);
	//PlayerCollider* getPlayerColliderComponent();
	static Snail* create(MainLayer* layer);

	float getTimer();
	void setTimer(float seconds);


private:
	float m_timer = 3.0;

	MainLayer* m_layer;
	bool m_isAlive = true;
	bool m_isDead = false;
	float m_speed = 100.0f;
	Point m_moveDirection;
	bool m_isForward = true;
	//PlayerCollider* m_pcollider;

	Action* m_pCrouchAction;
	Action* m_pPunchAction;
	Action* m_pPunch1Action;
	Action* m_pPunch2Action;
	Action* m_pDeathAction;
	Action* m_pHitAction;

	Animation* m_pCrouchCycleFrames;
	Animation* m_pPunch_1Frames;
	Animation* m_pPunch_2Frames;
	Animation* m_pDeathFrames;
	Animation* m_pHitFrames;

	Vector<SpriteFrame*> frames;
	String* m_pSpriteString;
	SpriteFrame* m_pFrame;

	SpriteFrameCache* m_pSpriteFrame;
	SpriteBatchNode* m_pSpriteBatch;

	Player* m_pPlayer = nullptr;

	Point playerPos;
	Point snailPos;

	//bool m_topCollision;
	//bool m_bottomColWhileTopCol;
	//Ground* m_topCollisionGround;
};

#endif // __SNAIL_H__