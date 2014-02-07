#ifndef __BASE_ENEMY_H__
#define __BASE_ENEMY_H__

#include "Moveable.h"
//TODO #include player

//die verschiedenen Zustände
enum Moods
{
	E_MoodWalk = 0,
	E_MoodAttack = 1,
	E_MoodDie = 2
};

class BaseEnemy : public Moveable
{

protected:

	//aktueller Zustand
	int mood;

	//Zustands Timer
	float timer;

	//ab welcher range soll der enemy angreifen
	float attackdistance;

	//wie lange nach angriff laufen
	virtual float walkTime();

	//Zustand manuell setzen
	virtual void setMood(int newMood);

	//nächster Zustand wird automatisch gesetzt
	virtual void chooseMood();

	//gibt true zurück wenn in attack range
	virtual bool canAttack();

public:

	BaseEnemy();
	virtual ~BaseEnemy();

	//Enemy Health
	int health = 10;

	//update
	virtual void update(float dt);

	//Walk-Zustand
	virtual void moodWalk(float dt);

	//Attack-Zustand
	virtual void moodAttack(float dt);

	//Die-Zustand
	virtual void moodDie(float dt);

	//lebt der enemy ?
	bool m_isAlive = true;

private:

};

#endif // __BASE_ENEMY_H__