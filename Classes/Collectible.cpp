#include "Collectible.h"
#include "Player.h"

Collectible::Collectible(MainLayer* parent) : Ground()
{
	m_pLayer = parent;
	this->autorelease();
	m_pLayer->schedule(cocos2d::SEL_SCHEDULE(&Collectible::update));
}

void Collectible::update(float _dt)
{
	getColliderComponent()->update(_dt);
	collisionCheck();
}

void Collectible::collisionCheck()
{
	Player* player = m_pLayer->getPlayer();
	Collider* myCol = getColliderComponent();
	PlayerCollider* plCol = player->getPlayerColliderComponent();

	if (myCol->getCollisionRectangle().intersectsRect(plCol->getBottomCollider())
		|| myCol->getCollisionRectangle().intersectsRect(plCol->getLeftCollider())
		|| myCol->getCollisionRectangle().intersectsRect(plCol->getRightCollider()))
		onCollidedWithPlayer(player);
}