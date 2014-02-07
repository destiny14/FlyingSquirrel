#ifndef __SNAIL_H__
#define __SNAIL_H__

#include "Moveable.h"
#include "BaseEnemy.h"
//TODO #include player


class Snail : public BaseEnemy
{
protected:

	Snail();
	virtual ~Snail();

	float walkTime();

	bool canAttack();

	void update(float dt);

	void moodWalk(float dt);

	void moodAttack(float dt);

	void moodDie(float dt);

public:

private:

	bool m_isAlive = true;

};


#endif // __SNAIL_H__