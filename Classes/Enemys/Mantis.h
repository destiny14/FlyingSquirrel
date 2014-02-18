#ifndef __MANTIS_H__
#define __MANTIS_H__

#include "Moveable.h"
//TODO #include player


class Mantis : public Moveable
{
protected:

	Mantis();
	virtual ~Mantis();

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

	Mantis* create(Point position, MainLayer* layer);

	CREATE_FUNC(Mantis);

private:

	bool m_isForward = true;

	Texture* m_ptex = nullptr;

};

#endif // __MANTIS_H__