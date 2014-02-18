#ifndef __WORM_H__
#define __WORM_H__

#include "Moveable.h"
//TODO #include player


class Worm : public Moveable
{
protected:

	Worm();
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

	static Worm* create(Point position, MainLayer* layer);

	CREATE_FUNC(Worm);

private:

	bool m_isForward = true;

	Texture* m_ptex = nullptr;

};

#endif // __WORM_H__