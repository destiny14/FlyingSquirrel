#ifndef __CRYSTAL_H__
#define __CRYSTAL_H__

#define TAG_CRYSTAL 75669873

#include "../../Collectible.h"

class CollectibleCrystal : public Collectible
{
public:
	CollectibleCrystal(MainLayer* layer);

	static CollectibleCrystal* create(MainLayer* layer);
	static int getCrystalCount() { return crystalCount > 4 ? 4 : crystalCount; }
	static void addCrystal(int c) { crystalCount += c; c = c > 4 ? 4 : c; c = c < 0 ? 0 : c; }
protected:
	virtual void initCollectible() override;
	virtual void onCollidedWithPlayer(Player* _player) override;
	static int crystalCount;
};

#endif