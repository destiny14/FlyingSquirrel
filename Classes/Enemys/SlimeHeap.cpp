#include "SlimeHeap.h"

USING_NS_CC;

const float m_timerUp = -1000.0f;

SlimeHeap::SlimeHeap()
{
	mood = E_MoodWalk;
	timer = m_timerUp;
	attackdistance = 50.0f;
	m_isAlive = true;
}

SlimeHeap::~SlimeHeap()
{

}

float SlimeHeap::walkTime()
{
	return 2.0f;
}

bool SlimeHeap::canAttack()
{
	//TODO attackrange <= distanz zum spieler
	return true;
}

void SlimeHeap::update(float dt)
{

}

void SlimeHeap::moodWalk(float dt)
{

}

void SlimeHeap::moodAttack(float dt)
{

}

void SlimeHeap::moodDie(float dt)
{

}
