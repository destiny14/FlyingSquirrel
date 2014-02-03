#include "cocos2d.h"
#include "Moveable.h"
#include "LevelLayer.h"
#include "Player.h"
#include "..\Components\Collider.h"

Player* Player::create(char* filename, MainLayer* parent)
{
	Player* player = new Player();
	Texture* tex = Texture::create(filename);
	if (tex)
	{
		player->setTexture(tex);
		player->setCollider();
		player->setParent(parent);
		player->setGround(false);
		return player;
	}
	return nullptr;
}

Player::Player() {}

Player::~Player() {}

void Player::setCollider()
{
	Sprite* sprite = getSprite();
	Rect boundingBox = sprite->getBoundingBox();
	m_leftCollider = Rect(boundingBox.origin.x, boundingBox.origin.y + 10, 10, boundingBox.size.height - 10);
	m_rightCollider = Rect(boundingBox.origin.x + (boundingBox.size.width - 10), boundingBox.origin.y + 10, 10, boundingBox.size.height - 10);
	m_bottomCollider = Rect(boundingBox.origin.x + 10, boundingBox.origin.y, boundingBox.size.width - 20, 10);
}

void Player::updateCollider()
{
	Rect oldCollider = getLeftCollider();
	setLeftCollider(oldCollider.size.width, oldCollider.size.height);
	oldCollider = getRightCollider();
	setRightCollider(oldCollider.size.width, oldCollider.size.height);
	oldCollider = getBottomCollider();
	setBottomCollider(oldCollider.size.width, oldCollider.size.height);
	float y = getPositionY();
	Rect bb = getSprite()->getBoundingBox();
}

void Player::setLeftCollider(float width, float height) 
{	 
	m_leftCollider = Rect(getSprite()->getBoundingBox().origin.x, getSprite()->getBoundingBox().origin.y + 10, width, height);
}	 

void Player::setRightCollider(float width, float height)
{
	m_rightCollider = Rect(getSprite()->getBoundingBox().origin.x + (getSprite()->getBoundingBox().size.width - width), getSprite()->getBoundingBox().origin.y + 10, width, height);
}

void Player::setBottomCollider(float width, float height)
{
	m_bottomCollider = Rect(getSprite()->getBoundingBox().origin.x + 10, getSprite()->getBoundingBox().origin.y, width, height);
}

Rect Player::getBottomCollider()
{
	return m_bottomCollider;
}

Rect Player::getLeftCollider()
{
	return m_leftCollider;
}

Rect Player::getRightCollider()
{
	return m_rightCollider;
}

void Player::update(float dt)
{
	Moveable::update(dt, true);
	updateCollider();
	
	CheckForCollisions();
}

void Player::CheckForCollisions()
{
	list<Ground*> physObj = getParent()->getPhysicsObjects();
	for (Ground* g : physObj)
	{
		if (g->getGround() == true)
		{
			Collider* c = dynamic_cast<Collider*>(g->getComponent("collider"));
			if (c->getCollisionRectangle().intersectsRect(getBottomCollider()))
			{
				// kollision
				setGrounded(true);
			}
		}
	}
}