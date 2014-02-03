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

	PlayerCollider* collider = PlayerCollider::create(boundingBox.size.width, boundingBox.size.height);
	this->addComponent(collider);
}

//void Player::updateCollider()
//{
//	Rect oldCollider = getLeftCollider();
//	setLeftCollider(oldCollider.size.width, oldCollider.size.height);
//	oldCollider = getRightCollider();
//	setRightCollider(oldCollider.size.width, oldCollider.size.height);
//	oldCollider = getBottomCollider();
//	setBottomCollider(oldCollider.size.width, oldCollider.size.height);
//	float y = getPositionY();
//	Rect bb = getSprite()->getBoundingBox();
//}

PlayerCollider* Player::getPlayerColliderComponent()
{
	return dynamic_cast<PlayerCollider*>(this->getComponent("playerCollider"));
}


void Player::update(float dt)
{
	Moveable::update(dt, true);
	PlayerCollider* p = getPlayerColliderComponent();
	if (p != nullptr)
		p->update(dt);
	
	CheckForCollisions();
}

void Player::CheckForCollisions()
{
	list<Ground*> physObj = getParent()->getPhysicsObjects();
	for (Ground* g : physObj)
	{
		if (g->getGround() == true)
		{
			Collider* c = g->getColliderComponent();
			if (c->getCollisionRectangle().intersectsRect(getPlayerColliderComponent()->getBottomCollider()))
			{
				// kollision (boden)
				setGrounded(true);
			}
		}
	}
}