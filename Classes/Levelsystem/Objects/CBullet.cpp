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
	CheckForCollisions();

	this->setPositionX(this->getPosition().x + (m_force * m_direction));
	this->getSprite()->setRotation(this->getSprite()->getRotation() + (m_force * m_direction));
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
		m_shooter->deleteBullet(this);
	}
}

void Bullet::CheckForCollisions()
{
	list<Ground*>* physObj = this->getParent()->getPhysicsObjects();
	for (Ground* g : *physObj)
	{
		if (g->getGround() == true)
		{
			Collider* c = dynamic_cast<Collider*>(g->getComponent("collider"));
			Collider* c2 = getColliderComponent();
			if (c->getCollisionRectangle().intersectsRect(getColliderComponent()->getCollisionRectangle()))
			{
				this->destroy();
			}
		}
	}
}