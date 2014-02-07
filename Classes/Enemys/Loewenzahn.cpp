#include "Loewenzahn.h"

USING_NS_CC;

const float m_timerUp = -1000.0f;

Loewenzahn::Loewenzahn()
{
	mood = E_MoodWalk;
	timer = m_timerUp;
	attackdistance = 50.0f;
	m_isAlive = true;
}

Loewenzahn::~Loewenzahn()
{

}

float Loewenzahn::walkTime()
{
	return 2.0f;
}

bool Loewenzahn::canAttack()
{
	//TODO attackrange <= distanz zum spieler
	return true;
}

void Loewenzahn::update(float dt)
{

}

void Loewenzahn::moodWalk(float dt)
{

}

void Loewenzahn::moodAttack(float dt)
{

}

void Loewenzahn::moodDie(float dt)
{

}
