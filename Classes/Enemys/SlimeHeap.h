#ifndef __SLIMEHEAP_H__
#define __SLIMEHEAP_H__

#include "Moveable.h"
//TODO #include player

enum Moods
{
	E_MoodWalk = 0,
	E_MoodAttack = 1,
	E_MoodDie = 2
};

class SlimeHeap : public Moveable
{
protected:

	SlimeHeap();
	virtual ~SlimeHeap();

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

	SlimeHeap* create(Point position, MainLayer* layer);

	CREATE_FUNC(SlimeHeap);

private:

	bool m_isForward = true;

	Texture* m_ptex = nullptr;

};

#endif // __SLIMEHEAP_H__