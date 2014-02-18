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
	attackRange = 20.0f;
	m_isAlive = true;

	return true;
}

void Snail::setCollider()
{
	Sprite* sprite = getSprite();
	Rect boundingBox = sprite->getBoundingBox();

	Collider* collider = Collider::create(240.0f, 165.0f);
	this->addComponent(collider);
}

void Snail::update(float dt)
{
	Moveable::update(dt, false);	

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
	
	if (m_timer >= 0)
	{
		m_moveDirection.x -= 1.0f;
		m_timer -= dt;
	}
	else if (m_timer < 0)
	{
		m_moveDirection.x += 1.0f;
		m_timer -= dt;
	}
	if (m_timer <= -3)
	{
		m_moveDirection.x = 0.0f;
		m_timer = 3;
	}

	getTexture()->setPosition(getTexture()->getPosition() + m_moveDirection * dt * m_speed);
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
	return false;
}

