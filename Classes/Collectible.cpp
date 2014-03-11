#include "Collectible.h"
#include "Player.h"
#include "MainLayer.h"

Collectible::Collectible(MainLayer* parent) : Ground(parent->physic)
{
	m_pLayer = parent;
}

bool Collectible::init()
{
	if (!Ground::init())
		return false;
	initCollectible();
	m_pLayer->addChild(getTexture()->getSprite());
	return true;
}

void Collectible::deleteCollectible()
{
	getSprite()->removeFromParentAndCleanup(true);
	this->removeFromParentAndCleanup(true);
}

bool Collectible::onCollision(PhysicsObject* _other, int myColliderTag)
{
	if (_other->getTag() != TAG_PLAYER) return false;

	onCollidedWithPlayer(dynamic_cast<Player*>(_other));
	return false;
}