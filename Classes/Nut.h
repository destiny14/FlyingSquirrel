#ifndef __NUT_H__
#define __NUT_H__

#include "Collectible.h"

class Nut : public Collectible
{
public:
	Nut(MainLayer* layer);

protected:
	void onCollidedWithPlayer(Player* _player) override;
};

#endif