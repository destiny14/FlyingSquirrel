#include "Worm.h"

USING_NS_CC;

Worm::Worm()
{
}

Worm::~Worm()
{
}

Worm* Worm::create(Point position, MainLayer* layer)
{
	Worm* snail = new Worm();

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

bool Worm::init()
{
	this->schedule(schedule_selector(Worm::update));

	mood = E_MoodWalk;
	attackRange = 20.0f;
	m_isAlive = true;

	return true;
}

void Worm::update(float dt)
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
void Worm::moodWalk(float dt)
{
	auto moveAction = MoveTo::create(2.0f, m_ptex->getPosition() + Point(200, 0));
	auto moveActionEnded = CallFuncN::create(this, callfuncN_selector(Worm::moveActionCompleted));
	m_ptex->getSprite()->runAction(Sequence::create(moveAction, moveActionEnded, nullptr));
}

//TODO
void Worm::moodAttack(float dt)
{
	//animation + attack
}

//TODO
void Worm::moodDie(float dt)
{
	//animation sterben
}

//TODO
bool Worm::canAttack()
{
	//TODO attackrange <= distanz zum spieler
	return true;
}

void Worm::moveActionCompleted(Node* pSender)
{
	auto sprite = dynamic_cast<Sprite*>(pSender);
	FiniteTimeAction* moveAction;

	if (m_isForward)
		moveAction = MoveTo::create(2.0f, sprite->getPosition() + Point(-200, 0));
	else
		moveAction = MoveTo::create(2.0f, sprite->getPosition() + Point(200, 0));

	auto moveActionEnded = CallFuncN::create(this, callfuncN_selector(Worm::moveActionCompleted));
	sprite->runAction(Sequence::create(moveAction, moveActionEnded, nullptr));

	m_isForward = !m_isForward;
}