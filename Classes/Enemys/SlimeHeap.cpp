#include "SlimeHeap.h"

USING_NS_CC;

SlimeHeap::SlimeHeap()
{
}

SlimeHeap::~SlimeHeap()
{
}

SlimeHeap* SlimeHeap::create(Point position, MainLayer* layer)
{
	SlimeHeap* snail = new SlimeHeap();

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

bool SlimeHeap::init()
{
	this->schedule(schedule_selector(SlimeHeap::update));

	mood = E_MoodWalk;
	attackRange = 20.0f;
	m_isAlive = true;

	return true;
}

void SlimeHeap::update(float dt)
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
void SlimeHeap::moodWalk(float dt)
{
	auto moveAction = MoveTo::create(2.0f, m_ptex->getPosition() + Point(200, 0));
	auto moveActionEnded = CallFuncN::create(this, callfuncN_selector(SlimeHeap::moveActionCompleted));
	m_ptex->getSprite()->runAction(Sequence::create(moveAction, moveActionEnded, nullptr));
}

//TODO
void SlimeHeap::moodAttack(float dt)
{
	//animation + attack
}

//TODO
void SlimeHeap::moodDie(float dt)
{
	//animation sterben
}

//TODO
bool SlimeHeap::canAttack()
{
	//TODO attackrange <= distanz zum spieler
	return true;
}

void SlimeHeap::moveActionCompleted(Node* pSender)
{
	auto sprite = dynamic_cast<Sprite*>(pSender);
	FiniteTimeAction* moveAction;

	if (m_isForward)
		moveAction = MoveTo::create(2.0f, sprite->getPosition() + Point(-200, 0));
	else
		moveAction = MoveTo::create(2.0f, sprite->getPosition() + Point(200, 0));

	auto moveActionEnded = CallFuncN::create(this, callfuncN_selector(SlimeHeap::moveActionCompleted));
	sprite->runAction(Sequence::create(moveAction, moveActionEnded, nullptr));

	m_isForward = !m_isForward;
}