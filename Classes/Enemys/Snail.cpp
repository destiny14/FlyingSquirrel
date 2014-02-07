#include "Snail.h"

USING_NS_CC;

const float m_timerUp = -1000.0f;

Snail::Snail()
{
	mood = E_MoodWalk;
	timer = m_timerUp;
	attackdistance = 50.0f;
	m_isAlive = true;
}

Snail::~Snail()
{

}

float Snail::walkTime()
{
	return 2.0f;
}

bool Snail::canAttack()
{
	//TODO attackrange <= distanz zum spieler
	return true;
}

void Snail::update(float dt)
{

}

void Snail::moodWalk(float dt)
{

}

void Snail::moodAttack(float dt)
{

}

void Snail::moodDie(float dt)
{

}
