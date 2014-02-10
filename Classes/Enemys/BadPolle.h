#ifndef __BADPOLLE_H__
#define __BADPOLLE_H__

#include "Moveable.h"
#include "BaseEnemy.h"
//TODO #include player


class BadPolle : public BaseEnemy
{
protected:

	BadPolle();
	virtual ~BadPolle();

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


#endif // __BADPOLLE_H__