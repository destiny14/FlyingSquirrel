#include "Nut.h"
#include "Player.h"

CollectibleNut::CollectibleNut(MainLayer* layer) : Collectible(layer)
{}

CollectibleNut* CollectibleNut::create(MainLayer* layer)
{
	CollectibleNut* ret = new CollectibleNut(layer);

	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}

	return nullptr;
}

void CollectibleNut::initCollectible()
{
	setTexture(Texture::create("Resources/pictures/generic/nuss.png"));
	setTag(TAG_NUT);
}

void CollectibleNut::onCollidedWithPlayer(Player* _player)
{
	_player->setNuts(_player->getNuts() + 1);
	deleteCollectible();
}