#ifndef __COLLECTIBLE_H__
#define __COLLECTIBLE_H__

#include "Levelsystem\Objects\Ground.h"
#include "Levelsystem\Layers\MainLayer.h"

class Player;

class Collectible : public Ground
{
public:
	Collectible(MainLayer* parent);
	void update(float dt) override;
	bool init() override;
protected:
	void deleteCollectible();
	virtual void initCollectible() = 0;
	virtual void onCollidedWithPlayer(Player* _player) = 0;
private:
	MainLayer* m_pLayer;
	void collisionCheck();
};

#endif