#ifndef __LOEWENZAHN_H__
#define __LOEWENZAHN_H__

#include "Moveable.h"
//TODO #include player


class Loewenzahn : public Moveable
{
protected:

	Loewenzahn();
	virtual ~Loewenzahn();

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

	Loewenzahn* create(MainLayer* layer);

	CREATE_FUNC(Loewenzahn);

private:

	bool m_isForward = true;

};

#endif // __LOEWENZAHN_H__