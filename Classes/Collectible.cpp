#include "Collectible.h"
#include "Player.h"

Collectible::Collectible(MainLayer* parent) : Ground()
{
	m_pLayer = parent;
}

void Collectible::update(float _dt)
{
	getColliderComponent()->update(_dt);
	collisionCheck();
}

bool Collectible::init()
{
	if (!Ground::init())
		return false;
	initCollectible();
	setCollider();
	m_pLayer->addChild(getTexture()->getSprite());
	return true;
}

void Collectible::deleteCollectible()
{
	getSprite()->removeFromParentAndCleanup(true);
	this->removeFromParentAndCleanup(true);
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