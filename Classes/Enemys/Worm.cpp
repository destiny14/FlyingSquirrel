#include "Worm.h"

USING_NS_CC;

const float m_timerUp = -1000.0f;

Worm::Worm()
{
	mood = E_MoodWalk;
	timer = m_timerUp;
	attackdistance = 50.0f;
	m_isAlive = true;
}

Worm::~Worm()
{

}

float Worm::walkTime()
{
	return 2.0f;
}

bool Worm::canAttack()
{
	//TODO attackrange <= distanz zum spieler
	return true;
}

void Worm::update(float dt)
{

}

void Worm::moodWalk(float dt)
{

}

void Worm::moodAttack(float dt)
{

}

void Worm::moodDie(float dt)
{

}
