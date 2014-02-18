#ifndef __BADPOLLE_H__
#define __BADPOLLE_H__

#include "Moveable.h"
//TODO #include player


class BadPolle : public Moveable
{
protected:

	BadPolle();
	virtual ~BadPolle();
	
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

	BadPolle* create(Point position, MainLayer* layer);

	CREATE_FUNC(BadPolle);

private:

	bool m_isForward = true;

	Texture* m_ptex = nullptr;

};

#endif // __BADPOLLE_H__