#ifndef __SNAIL_H__
#define __SNAIL_H__

#include "cocos2d.h"
#include "Moveable.h"
#include <vector>
#include "Levelsystem\Objects\Shooter.h"
#include "Levelsystem\Objects\Player.h"
#include "Levelsystem\Layers\MainLayer.h"
#include "Components\PlayerCollider.h"
#include "Levelsystem\Objects\Ground.h"

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

	int attackRange = 180;
	void update(float dt);
	bool m_isAlive = true;
	PlayerCollider* getPlayerColliderComponent();
	static Snail* create(MainLayer* layer);

private:

	float m_timer = 3.0;
	float m_speed = 100.0f;
	Point m_moveDirection;
	bool m_isForward = true;
	PlayerCollider* m_pcollider;

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

	Player* m_pPlayer;

	int playerPosX;
	int snailPosX;

	bool m_topCollision;
	bool m_bottomColWhileTopCol;
	Ground* m_topCollisionGround;
};

#endif // __SNAIL_H__