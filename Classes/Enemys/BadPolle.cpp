#include "BadPolle.h"

USING_NS_CC;

const float m_timerUp = -1000.0f;

BadPolle::BadPolle()
{
	mood = E_MoodWalk;
	timer = m_timerUp;
	attackdistance = 50.0f;
	m_isAlive = true;
}

BadPolle::~BadPolle()
{

}

float BadPolle::walkTime()
{
	return 2.0f;
}

bool BadPolle::canAttack()
{
	//TODO attackrange <= distanz zum spieler
	return true;
}

void BadPolle::update(float dt)
{

}

void BadPolle::moodWalk(float dt)
{

}

void BadPolle::moodAttack(float dt)
{

}

void BadPolle::moodDie(float dt)
{

}
