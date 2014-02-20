#ifndef __NUT_H__
#define __NUT_H__

#include "Collectible.h"

class CollectibleNut : public Collectible
{
public:
	CollectibleNut(MainLayer* layer);

protected:
	void onCollidedWithPlayer(Player* _player) override;
};

#endif