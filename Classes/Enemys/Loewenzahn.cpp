#include "Loewenzahn.h"

USING_NS_CC;

Loewenzahn::Loewenzahn()
{
}

Loewenzahn::~Loewenzahn()
{
}

Loewenzahn* Loewenzahn::create(MainLayer* layer)
{
	Loewenzahn* loewenzahn = new Loewenzahn();


	Texture* m_ptex = Texture::create("loewenzahn.png");

	if (m_ptex)
	{
		loewenzahn->setTexture(m_ptex);
		loewenzahn->setCollider();
		loewenzahn->setParent(layer);

		loewenzahn->init();

		return loewenzahn;
	}

	return nullptr;
}

bool Loewenzahn::init()
{
	this->schedule(schedule_selector(Loewenzahn::update));

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
	auto moveAction = MoveTo::create(2.0f, getTexture()->getPosition() + Point(200, 0));
	auto moveActionEnded = CallFuncN::create(this, callfuncN_selector(Loewenzahn::moveActionCompleted));
	getTexture()->getSprite()->runAction(Sequence::create(moveAction, moveActionEnded, nullptr));
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