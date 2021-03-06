#include "Worm.h"
#include "MainLayer.h"

USING_NS_CC;

Worm::Worm(PhysicsEngine* _pEn) : Moveable(_pEn)
{
}

Worm::~Worm()
{
}

Worm* Worm::create(MainLayer* layer)
{
	Worm* worm = new Worm(layer->physic);


	Texture* m_ptex = Texture::create("worm.png");

	if (m_ptex)
	{
		worm->setTexture(m_ptex);
		worm->setSizeToTexture();
		worm->setParentLayer(layer);

		worm->init();


		return worm;
	}

	return nullptr;
}

bool Worm::init()
{
	this->schedule(schedule_selector(Worm::update));

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
	auto moveAction = MoveTo::create(2.0f, getTexture()->getPosition() + Point(200, 0));
	auto moveActionEnded = CallFuncN::create(this, callfuncN_selector(Worm::moveActionCompleted));
	getTexture()->getSprite()->runAction(Sequence::create(moveAction, moveActionEnded, nullptr));
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