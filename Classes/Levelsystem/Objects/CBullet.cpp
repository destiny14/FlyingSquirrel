#include "cocos2d.h"
#include "Moveable.h"
#include "LevelLayer.h"
#include "Bullet.h"
#include "..\Components\Collider.h"
#include "Shooter.h"

Bullet* Bullet::createNut(Shooter* shooter, MainLayer* parent, Point position, float direction, float force)
{
	Bullet* bullet = new Bullet();
	Texture* tex = Texture::create("nuss.png");
	bullet->m_pSnail = parent->getSnail();
	bullet->m_pSlimeHeap = parent->getSlimeHeap();
	tex->retain();

	bullet->setTexture(tex);
	bullet->setCollider();
	bullet->setParent(parent);
	bullet->setGround(false);
	bullet->setPosition(position.x + (100.0f * direction), position.y + 25.0f);
	bullet->setAffectedByGravity(true);
	bullet->getSprite()->setScale(0.5f);
	
	bullet->init(shooter, direction, force);

	return bullet;
}

Bullet::Bullet() {}

Bullet::~Bullet() {}

bool Bullet::init(Shooter* shooter, float direction, float force)
{
	m_shooter = shooter;
	m_direction = direction;
	m_force = force;

	m_bullettype = Nut;

	return true;
}

void Bullet::update(float dt)
{
	Moveable::update(dt, false);
	this->setPositionX(this->getPosition().x + (m_force * m_direction));
	this->getSprite()->setRotation(this->getSprite()->getRotation() + (m_force * m_direction));
	CheckForCollisions();
}

void Bullet::setCollider()
{
	Sprite* sprite = getSprite();
	Rect boundingBox = sprite->getBoundingBox();

	Collider* collider = Collider::create(10.0f, 10.0f);
	this->addComponent(collider);
}

void Bullet::destroy()
{
	if (m_bullettype == Bullettype::Nut)
	{
		this->getParent()->removeChild(this->getSprite());
		this->removeFromParent();
		m_shooter->deleteBullet(this);
	}
}

void Bullet::CheckForCollisions()
{
	if (m_pSnail != nullptr)
	{
		if (m_pSnail->getColliderComponent()->getCollisionRectangle().intersectsRect(this->getColliderComponent()->getCollisionRectangle()))
		{
			m_pSnail->killIt();
		}
	}
	if (m_pSlimeHeap != nullptr)
	{
		if (m_pSlimeHeap->getColliderComponent()->getCollisionRectangle().intersectsRect(this->getColliderComponent()->getCollisionRectangle()))
		{
			m_pSlimeHeap->killIt();
		}
	} 

	list<Ground*>* physObj = this->getParent()->getPhysicsObjects();
	list<Ground*> desObj;
	for (Ground* g : *physObj)
	{
			if (g->getGround())
			{
				Collider* c = dynamic_cast<Collider*>(g->getComponent("collider"));
				Collider* c2 = getColliderComponent();
				if (c->getCollisionRectangle().intersectsRect(getColliderComponent()->getCollisionRectangle()))
				{
					desObj.push_back(g);
				}
			}
			
	}
	for (list<Ground*>::iterator itr = desObj.begin(); itr != desObj.end();)
	{
		this->destroy();
		itr = desObj.erase(itr);
	}
}