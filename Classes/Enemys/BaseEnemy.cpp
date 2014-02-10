#include "BaseEnemy.h"

USING_NS_CC;

const float m_timerUp = -9999.0f;


BaseEnemy::BaseEnemy()
{
	mood = E_MoodWalk;
	timer = m_timerUp;
	attackdistance = 50.0f;
	m_isAlive = true;
}

BaseEnemy::~BaseEnemy()
{

}

float BaseEnemy::walkTime()
{
	//gibt zeit zurück die zwischen 2 angriffe gewartet wird
	return 1.0f;
}

void BaseEnemy::setMood(int newMood)
{
	//setzt neuen Mood
	mood = newMood;

	//timer resetten
	timer = m_timerUp;
}

void BaseEnemy::chooseMood()
{
	//wechselt zwischen walk und attack zustand
	this->setMood((canAttack() ? E_MoodAttack : E_MoodWalk));
}

bool BaseEnemy::canAttack()
{
	//TODO attackrange <= distanz zum spieler
	return true;
}

void BaseEnemy::update(float dt)
{
	if (this->m_isAlive)
	{
		if (timer != m_timerUp)
		{
			timer -= dt;
		}

		switch (mood)
		{
		case E_MoodWalk:
			this->moodWalk(dt);
			break;
		case E_MoodAttack :
			this->moodAttack(dt);
			break;
		case E_MoodDie:
			this->moodDie(dt);
			break;
		}
	}
}

void BaseEnemy::moodWalk(float dt)
{
	// starting attack mood
	if (timer == m_timerUp)
		timer = 1.0f;

	// timer up
	else if (timer <= 0.0f)
		this->chooseMood();
}

void BaseEnemy::moodAttack(float dt)
{
	// starting attack mood
	if (timer == m_timerUp)
		timer = 1.0f;

	// timer up
	else if (timer <= 0.0f)
		this->chooseMood();
}

void BaseEnemy::moodDie(float dt)
{
	if (health <= 0)
	{
		//TODO Die
	}
}