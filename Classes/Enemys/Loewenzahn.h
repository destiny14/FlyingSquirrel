#ifndef __LOEWENZAHN_H__
#define __LOEWENZAHN_H__

#include "Moveable.h"
#include "BaseEnemy.h"
//TODO #include player


class Loewenzahn : public BaseEnemy
{
protected:

	Loewenzahn();
	virtual ~Loewenzahn();

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


#endif // __LOEWENZAHN_H__