#ifndef __SNAIL_H__
#define __SNAIL_H__

#include "Moveable.h"
//TODO #include player

class Snail : public Moveable
{
protected:

	Snail();
	virtual ~Snail();
		
	bool init();

	void setCollider();

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

	float m_timer = 3.0;

	float m_speed = 100.0f;

	Point m_moveDirection;

	bool m_isForward = true;

	Action* m_pMoveAction;

};

#endif // __SNAIL_H__