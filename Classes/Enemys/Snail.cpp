#include "Snail.h"

USING_NS_CC;

Snail::Snail()
{
}

Snail::~Snail()
{
}

Snail* Snail::create( MainLayer* layer)
{
	Snail* snail = new Snail();


	Texture* m_ptex = Texture::create("snail.png");

	if (m_ptex)
	{
		snail->setTexture(m_ptex);
		snail->setCollider();
		snail->setParent(layer);

		snail->init();

		return snail;
	}

	return nullptr;
}

bool Snail::init()
{
	this->schedule(schedule_selector(Snail::update));

	attackRange = 20.0f;
	m_isAlive = true;

	return true;
}

void Snail::update(float dt)
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
void Snail::moodWalk(float dt)
{
	auto moveAction = MoveTo::create(2.0f, getTexture()->getPosition() + Point(200, 0));
	auto moveActionEnded = CallFuncN::create(this, callfuncN_selector(Snail::moveActionCompleted));
	getTexture()->getSprite()->runAction(Sequence::create(moveAction, moveActionEnded, nullptr));
}

//TODO
void Snail::moodAttack(float dt)
{
	//animation + attack
}

//TODO
void Snail::moodDie(float dt)
{
	//animation sterben
}

//TODO
bool Snail::canAttack()
{
	//TODO attackrange <= distanz zum spieler
	return true;
}

void Snail::moveActionCompleted(Node* pSender)
{
	auto sprite = dynamic_cast<Sprite*>(pSender);
	FiniteTimeAction* moveAction;

	if (m_isForward)
		moveAction = MoveTo::create(2.0f, sprite->getPosition() + Point(-200, 0));
	else
		moveAction = MoveTo::create(2.0f, sprite->getPosition() + Point(200, 0));

	auto moveActionEnded = CallFuncN::create(this, callfuncN_selector(Snail::moveActionCompleted));
	sprite->runAction(Sequence::create(moveAction, moveActionEnded, nullptr));

	m_isForward = !m_isForward;
}