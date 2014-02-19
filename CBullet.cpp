#include "cocos2d.h"
#include "Moveable.h"
#include "LevelLayer.h"
#include "Bullet.h"
#include "..\Components\Collider.h"

Bullet* Bullet::createNut(MainLayer* parent, Point* position, Point* direction, float force)
{
	Bullet* bullet = new Bullet();
	Texture* tex = Texture::create("nuss.png");

	bullet->setTexture(tex);
	bullet->setCollider();
	bullet->setParent(parent);
	bullet->setGround(false);
	bullet->setPosition(position->x, position->y);

	m_pDirection = direction;
	m_force = force;

	m_bullettype = Nut;

	bullet->init();

	return bullet;
}

Bullet::Bullet() {}

Bullet::~Bullet() {}

bool Bullet::init()
{
	return true;
}

void Bullet::update(float dt)
{

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