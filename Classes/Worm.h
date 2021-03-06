#ifndef __WORM_H__
#define __WORM_H__

#include "Moveable.h"
//TODO #include player


class Worm : public Moveable
{
protected:

	Worm(PhysicsEngine* _pEn);
	virtual ~Worm();

	bool init();

	void update(float dt);

	bool canAttack();

	void moodWalk(float dt);

	void moodAttack(float dt);

	void moodDie(float dt);

	void moveActionCompleted(Node* pSender);


public:

	int mood = 1;

	int timer = 0;

	int attackRange = 20;

	bool m_isAlive = true;

	Worm* create(MainLayer* layer);

private:

	bool m_isForward = true;

};

#endif // __WORM_H__