#ifndef __MANTIS_H__
#define __MANTIS_H__

#include "Moveable.h"
#include "BaseEnemy.h"
//TODO #include player


class Mantis : public BaseEnemy
{
protected:

	Mantis();
	virtual ~Mantis();

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


#endif // __MANTIS_H__