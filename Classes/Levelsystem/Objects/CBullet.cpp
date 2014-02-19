#include "cocos2d.h"
#include "Moveable.h"
#include "LevelLayer.h"
#include "Bullet.h"
#include "..\Components\Collider.h"

Bullet* Bullet::createNut(MainLayer* parent, Point position, float direction, float force)
{
	Bullet* bullet = new Bullet();
	Texture* tex = Texture::create("nuss.png");
	tex->retain();

	bullet->setTexture(tex);
	bullet->setCollider();
	bullet->setParent(parent);
	bullet->setGround(false);
	bullet->setPosition(position.x + (150.0f * direction), position.y);
	bullet->setAffectedByGravity(true);

	bullet->init(direction, force);

	return bullet;
}

Bullet::Bullet() {}

Bullet::~Bullet() {}

bool Bullet::init(float direction, float force)
{
	m_direction = direction;
	m_force = force;

	m_bullettype = Nut;

	return true;
}

void Bullet::update(float dt)
{
	this->setPositionX(this->getPosition().x + (m_force * m_direction));
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

}