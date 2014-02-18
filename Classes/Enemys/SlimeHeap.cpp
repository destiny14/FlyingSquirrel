#include "SlimeHeap.h"

USING_NS_CC;

SlimeHeap::SlimeHeap()
{
}

SlimeHeap::~SlimeHeap()
{
}

SlimeHeap* SlimeHeap::create(MainLayer* layer)
{
	SlimeHeap* slimeHeap = new SlimeHeap();


	Texture* m_ptex = Texture::create("slimeHeap.png");

	if (m_ptex)
	{
		slimeHeap->setTexture(m_ptex);
		slimeHeap->setCollider();
		slimeHeap->setParent(layer);

		slimeHeap->init();

		return slimeHeap;
	}

	return nullptr;
}

bool SlimeHeap::init()
{
	this->schedule(schedule_selector(SlimeHeap::update));

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
	auto moveAction = MoveTo::create(2.0f, getTexture()->getPosition() + Point(200, 0));
	auto moveActionEnded = CallFuncN::create(this, callfuncN_selector(SlimeHeap::moveActionCompleted));
	getTexture()->getSprite()->runAction(Sequence::create(moveAction, moveActionEnded, nullptr));
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