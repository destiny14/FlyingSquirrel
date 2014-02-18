#include "Loewenzahn.h"

USING_NS_CC;

Loewenzahn::Loewenzahn()
{
}

Loewenzahn::~Loewenzahn()
{
}

Loewenzahn* Loewenzahn::create(Point position, MainLayer* layer)
{
	Loewenzahn* snail = new Loewenzahn();

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

bool Loewenzahn::init()
{
	this->schedule(schedule_selector(Loewenzahn::update));

	mood = E_MoodWalk;
	attackRange = 20.0f;
	m_isAlive = true;

	return true;
}

void Loewenzahn::update(float dt)
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
void Loewenzahn::moodWalk(float dt)
{
	auto moveAction = MoveTo::create(2.0f, m_ptex->getPosition() + Point(200, 0));
	auto moveActionEnded = CallFuncN::create(this, callfuncN_selector(Loewenzahn::moveActionCompleted));
	m_ptex->getSprite()->runAction(Sequence::create(moveAction, moveActionEnded, nullptr));
}

//TODO
void Loewenzahn::moodAttack(float dt)
{
	//animation + attack
}

//TODO
void Loewenzahn::moodDie(float dt)
{
	//animation sterben
}

//TODO
bool Loewenzahn::canAttack()
{
	//TODO attackrange <= distanz zum spieler
	return true;
}

void Loewenzahn::moveActionCompleted(Node* pSender)
{
	auto sprite = dynamic_cast<Sprite*>(pSender);
	FiniteTimeAction* moveAction;

	if (m_isForward)
		moveAction = MoveTo::create(2.0f, sprite->getPosition() + Point(-200, 0));
	else
		moveAction = MoveTo::create(2.0f, sprite->getPosition() + Point(200, 0));

	auto moveActionEnded = CallFuncN::create(this, callfuncN_selector(Loewenzahn::moveActionCompleted));
	sprite->runAction(Sequence::create(moveAction, moveActionEnded, nullptr));

	m_isForward = !m_isForward;
}