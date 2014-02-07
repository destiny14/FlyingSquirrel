#ifndef __SLIMEHEAP_H__
#define __SLIMEHEAP_H__

#include "Moveable.h"
#include "BaseEnemy.h"
//TODO #include player


class SlimeHeap : public BaseEnemy
{
protected:

	SlimeHeap();
	virtual ~SlimeHeap();

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


#endif // __SLIMEHEAP_H__