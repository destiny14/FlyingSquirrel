#include "Nut.h"
#include "Levelsystem\Objects\Player.h"

CollectibleNut::CollectibleNut(MainLayer* layer) : Collectible(layer)
{
	setTexture(Texture::create("nuss.png"));
}

void CollectibleNut::onCollidedWithPlayer(Player* _player)
{
	//_player->addNut();
	this->removeFromParentAndCleanup(true);
}