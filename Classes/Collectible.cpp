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
	scheduleUpdate();
	return true;
}

void Collectible::update(float _dt)
{
	Ground::update(_dt);

	if (m_toDel)
	{
		getSprite()->removeFromParentAndCleanup(true);
		this->removeFromParentAndCleanup(true);
	}
}

void Collectible::deleteCollectible()
{
	m_toDel = true;
}

bool Collectible::onCollision(PhysicsObject* _other, int myColliderTag)
{
	if (m_toDel) return false;
	if (_other->getTag() != TAG_PLAYER) return false;

	onCollidedWithPlayer(dynamic_cast<Player*>(_other));
	return false;
}