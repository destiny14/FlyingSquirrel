#ifndef __WORM_H__
#define __WORM_H__

#include "Moveable.h"
#include "BaseEnemy.h"
//TODO #include player


class Worm : public BaseEnemy
{
protected:

	Worm();
	virtual ~Worm();

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


#endif // __WORM_H__