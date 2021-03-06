#ifndef __NUT_H__
#define __NUT_H__
#define TAG_NUT 6969869

#include "Collectible.h"

class CollectibleNut : public Collectible
{
public:
	CollectibleNut(MainLayer* layer);

	static CollectibleNut* create(MainLayer* layer);

protected:
	void onCollidedWithPlayer(Player* _player) override;
	void initCollectible() override;
};

#endif