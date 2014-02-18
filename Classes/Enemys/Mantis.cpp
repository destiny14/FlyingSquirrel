#include "Mantis.h"

USING_NS_CC;

Mantis::Mantis()
{
}

Mantis::~Mantis()
{
}

Mantis* Mantis::create(Point position, MainLayer* layer)
{
	Mantis* mantis = new Mantis();

	mantis->init();

	m_ptex = Texture::create("mantis.png");

	if (m_ptex)
	{
		mantis->setPosition(position);
		mantis->setTexture(m_ptex);
		mantis->setCollider();
		mantis->setParent(layer);
		mantis->setGround(false);

		return mantis;
	}

	return nullptr;
}

bool Mantis::init()
{
	this->schedule(schedule_selector(Mantis::update));

	attackRange = 20.0f;
	m_isAlive = true;

	return true;
}

void Mantis::update(float dt)
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
void Mantis::moodWalk(float dt)
{
	auto moveAction = MoveTo::create(2.0f, m_ptex->getPosition() + Point(200, 0));
	auto moveActionEnded = CallFuncN::create(this, callfuncN_selector(Mantis::moveActionCompleted));
	m_ptex->getSprite()->runAction(Sequence::create(moveAction, moveActionEnded, nullptr));
}

//TODO
void Mantis::moodAttack(float dt)
{
	//animation + attack
}

//TODO
void Mantis::moodDie(float dt)
{
	//animation sterben
}

//TODO
bool Mantis::canAttack()
{
	//TODO attackrange <= distanz zum spieler
	return true;
}

void Mantis::moveActionCompleted(Node* pSender)
{
	auto sprite = dynamic_cast<Sprite*>(pSender);
	FiniteTimeAction* moveAction;

	if (m_isForward)
		moveAction = MoveTo::create(2.0f, sprite->getPosition() + Point(-200, 0));
	else
		moveAction = MoveTo::create(2.0f, sprite->getPosition() + Point(200, 0));

	auto moveActionEnded = CallFuncN::create(this, callfuncN_selector(Mantis::moveActionCompleted));
	sprite->runAction(Sequence::create(moveAction, moveActionEnded, nullptr));

	m_isForward = !m_isForward;
}