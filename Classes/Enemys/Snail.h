#ifndef __SNAIL_H__
#define __SNAIL_H__

#include "Moveable.h"
#include <vector>
#include "Levelsystem\Objects\Shooter.h"
//TODO #include player

class Snail : public Shooter
{
protected:

	Snail();
	virtual ~Snail();
		
	bool init();

	void setCollider(float width, float height);

	bool canAttack();

	void moodWalk(float dt);

	void moodAttack(float dt);

	void moodDie(float dt);

	void moveActionCompleted(Node* pSender);


public:

	int attackRange = 20;

	void update(float dt);

	bool m_isAlive = true;

	static Snail* create(MainLayer* layer);

private:

	bool punch1 = true;

	bool debugAttack = false;

	void CheckForCollisions();

	bool m_first = true;

	float m_timer = 3.0;

	float m_speed = 100.0f;

	Point m_moveDirection;

	bool m_isForward = true;

	Collider* m_pcollider;

	Action* m_pCrouchAction;
	Action* m_pPunchAction;
	Animate* m_pPunch1Action;
	Animate* m_pPunch2Action;
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

};

#endif // __SNAIL_H__