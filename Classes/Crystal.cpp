#include "Crystal.h"
#include "Player.h"

int CollectibleCrystal::crystalCount = 0;

CollectibleCrystal::CollectibleCrystal(MainLayer* layer) : Collectible(layer)
{
}

CollectibleCrystal* CollectibleCrystal::create(MainLayer* layer)
{
	CollectibleCrystal* ret = new CollectibleCrystal(layer);
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

void CollectibleCrystal::initCollectible()
{
	setTexture(Texture::create("Resources/pictures/generic/crystal.png"));
	setTag(TAG_CRYSTAL);
}

void CollectibleCrystal::onCollidedWithPlayer(Player* player)
{
	addCrystal(1);
	deleteCollectible();
}