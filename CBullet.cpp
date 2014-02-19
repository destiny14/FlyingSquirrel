#include "cocos2d.h"
#include "Moveable.h"
#include "LevelLayer.h"
#include "Bullet.h"
#include "..\Components\Collider.h"

Bullet* Bullet::create(char* filename, MainLayer* parent, Point* position)
{
	Bullet* bullet = new Bullet();
	Texture* tex = Texture::create(filename);

	if (tex)
	{
		bullet->setTexture(tex);
		bullet->setCollider();
		bullet->setParent(parent);
		bullet->setGround(false);

		bullet->init();

		return bullet;
	}
	else
	{
		return nullptr;
	}
}

Bullet::Bullet() {}

Bullet::~Bullet() {}

bool Bullet::init()
{

}

void Bullet::update(float dt)
{

}

void Bullet::setCollider()
{
	Sprite* sprite = getSprite();
	Rect boundingBox = sprite->getBoundingBox();

	// PlayerCollider* collider = PlayerCollider::create(160.0f, 250.0f);//boundingBox.size.width, boundingBox.size.height);
	//this->addComponent(collider);
}

void Bullet::destroy()
{

}