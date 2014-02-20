#ifndef __MANTIS_H__
#define __MANTIS_H__

#include "cocos2d.h"
#include "Moveable.h"
#include <vector>
#include "Levelsystem\Objects\Shooter.h"
#include "Levelsystem\Objects\Player.h"
#include "Levelsystem\Layers\MainLayer.h"
#include "Components\PlayerCollider.h"
#include "Levelsystem\Objects\Ground.h"

class Mantis : public Shooter
{
protected:

	Mantis();
	virtual ~Mantis();
	bool init();
	void setCollider(float width, float height);
	void CheckForCollisions();
	bool canAttack();
	void moodWalk(float dt);
	void moodAttack(float dt);
	void moodDie(float dt);
	void rangeAttack(float dt);

public:

	int attackRange_Meele = 450;
	int attackRange_Range = 280;
	void update(float dt);
	bool m_isAlive = true;
	PlayerCollider* getPlayerColliderComponent();
	static Mantis* create(MainLayer* layer);

private:

	float attackTimer = 5.0f;
	float m_speed = 100.0f;
	Point m_moveDirection;
	bool m_isForward = true;
	PlayerCollider* m_pcollider;

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

	Player* m_pPlayer;

	int playerPosX;
	int mantisPosX;

	bool m_topCollision;
	bool m_bottomColWhileTopCol;
	Ground* m_topCollisionGround;
};

#endif // __MANTIS_H__