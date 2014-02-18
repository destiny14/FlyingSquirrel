#include "BadPolle.h"

USING_NS_CC;

BadPolle::BadPolle()
{
}

BadPolle::~BadPolle()
{
}

BadPolle* BadPolle::create(Point position, MainLayer* layer)
{
	BadPolle* snail = new BadPolle();

	snail->init();

	m_ptex = Texture::create("snail.png");

	if (m_ptex)
	{
		snail->setPosition(position);
		snail->setTexture(m_ptex);
		snail->setCollider();
		snail->setParent(layer);
		snail->setGround(false);

		return snail;
	}

	return nullptr;
}

bool BadPolle::init()
{
	this->schedule(schedule_selector(BadPolle::update));

	mood = E_MoodWalk;
	attackRange = 20.0f;
	m_isAlive = true;

	return true;
}

void BadPolle::update(float dt)
{
	if (this->m_isAlive)
	{
		if (canAttack())
		{
			this->moodAttack(dt);
		}
		else
		{
			this->moodWalk(dt);
		}
	}
	else if (!(this->m_isAlive))
	{
		this->moodDie(dt);
	}
}

//TODO
void BadPolle::moodWalk(float dt)
{
	auto moveAction = MoveTo::create(2.0f, m_ptex->getPosition() + Point(200, 0));
	auto moveActionEnded = CallFuncN::create(this, callfuncN_selector(BadPolle::moveActionCompleted));
	m_ptex->getSprite()->runAction(Sequence::create(moveAction, moveActionEnded, nullptr));
}

//TODO
void BadPolle::moodAttack(float dt)
{
	//animation + attack
}

//TODO
void BadPolle::moodDie(float dt)
{
	//animation sterben
}

//TODO
bool BadPolle::canAttack()
{
	//TODO attackrange <= distanz zum spieler
	return true;
}

void BadPolle::moveActionCompleted(Node* pSender)
{
	auto sprite = dynamic_cast<Sprite*>(pSender);
	FiniteTimeAction* moveAction;

	if (m_isForward)
		moveAction = MoveTo::create(2.0f, sprite->getPosition() + Point(-200, 0));
	else
		moveAction = MoveTo::create(2.0f, sprite->getPosition() + Point(200, 0));

	auto moveActionEnded = CallFuncN::create(this, callfuncN_selector(BadPolle::moveActionCompleted));
	sprite->runAction(Sequence::create(moveAction, moveActionEnded, nullptr));

	m_isForward = !m_isForward;
}