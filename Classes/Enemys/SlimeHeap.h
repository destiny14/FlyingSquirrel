#ifndef __SLIMEHEAP_H__
#define __SLIMEHEAP_H__

#include "cocos2d.h"
#include "Moveable.h"
#include <vector>
#include "Levelsystem\Objects\Shooter.h"
#include "Levelsystem\Objects\Player.h"
#include "Levelsystem\Layers\MainLayer.h"
#include "Components\PlayerCollider.h"
#include "Levelsystem\Objects\Ground.h"

class SlimeHeap : public Shooter
{
protected:

	SlimeHeap();
	virtual ~SlimeHeap();
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
	//PlayerCollider* getPlayerColliderComponent();
	static SlimeHeap* create(MainLayer* layer);

private:

	float m_timer = 3.0;
	float m_speed = 100.0f;
	Point m_moveDirection;
	bool m_isForward = true;
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

	Player* m_pPlayer;

	int playerPosX;
	int slimePosX;

	//bool m_topCollision;
	//bool m_bottomColWhileTopCol;
	//Ground* m_topCollisionGround;
};

#endif // __SLIMEHEAP_H__