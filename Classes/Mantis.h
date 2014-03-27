#ifndef __MANTIS_H__
#define __MANTIS_H__

#define TAG_MANTIS 45678

#include "cocos2d.h"
#include "Moveable.h"
#include <vector>
#include "Shooter.h"
#include "Player.h"
#include "MainLayer.h"
#include "Ground.h"
#include "Mantis.h"


class Mantis : public Shooter
{
protected:

	Mantis(PhysicsEngine* _pEn);
	virtual ~Mantis();
	bool init();
	void CheckForCollisions();
	bool canAttack();
	void moodWalk(float dt);
	void moodAttack(float dt);
	void moodDie(float dt);
	void rangeAttack(float dt);

public:

	int attackRange_Meele = 545;
	int attackRange_Range = 2000;
	void update(float dt);
	bool m_isAlive = true;
	static Mantis* create(PhysicsEngine* _pEn, MainLayer* layer);
	void applyDamage();
	virtual bool onCollision(PhysicsObject* _other, int _myColliderTag);

private:

	MainLayer* m_layer;
	bool m_first = false;
	int m_health = 10;
	bool m_isDead = false;
	float attackTimer = 5.0f;
	float m_speed = 100.0f;
	Point m_moveDirection;
	bool m_isForward = true;

	Action* m_pIdleAction;
	Action* m_pRunAction;
	Action* m_pAttackAction;
	Action* m_pRangeAttackAction;
	Action* m_pDeathAction;
	Action* m_pHitAction;

	Animation* m_pIdleFrames;
	Animation* m_pRunFrames;
	Animation* m_pAttackFrames;
	Animation* m_pRangeAttackFrames;
	Animation* m_pDeathFrames;
	Animation* m_pHitFrames;

	Vector<SpriteFrame*> frames;
	String* m_pSpriteString;
	SpriteFrame* m_pFrame;

	SpriteFrameCache* m_pSpriteFrame;
	SpriteBatchNode* m_pSpriteBatch;

	Player* m_pPlayer = nullptr;

	Point playerPos;
	Point mantisPos;

	//bool m_topCollision;
	//bool m_bottomColWhileTopCol;
	//Ground* m_topCollisionGround;
};

#endif // __MANTIS_H__