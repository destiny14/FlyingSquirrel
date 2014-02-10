#include "Mantis.h"

USING_NS_CC;

const float m_timerUp = -1000.0f;

Mantis::Mantis()
{
	mood = E_MoodWalk;
	timer = m_timerUp;
	attackdistance = 50.0f;
	m_isAlive = true;
}

Mantis::~Mantis()
{

}

float Mantis::walkTime()
{
	return 2.0f;
}

bool Mantis::canAttack()
{
	//TODO attackrange <= distanz zum spieler
	return true;
}

void Mantis::update(float dt)
{

}

void Mantis::moodWalk(float dt)
{

}

void Mantis::moodAttack(float dt)
{

}

void Mantis::moodDie(float dt)
{

}
